#include "MovieLibraryWindow.h"

#include <FL/fl_types.h>
#include <Fl/fl_draw.H>
#include <Fl/Fl_File_Chooser.H>

#include "DeleteMovieWindow.h"
#include "AddMovieWindow.h"
#include "../fileio/MovieLoader.h"
#include "../fileio/MovieSaver.h"
#include "../model/MovieList.h"

#define DIAGNOSTIC_OUTPUT

#ifdef DIAGNOSTIC_OUTPUT
#include <iostream>
#endif

namespace view
{

MovieLibraryWindow::MovieLibraryWindow(int width, int height, const char* title) : Fl_Window(width, height, title)
{
    begin();

    this->sortingOutputLabel = new Fl_Output(100, 25, 0, 0, "Sort order:");
    createAndDisplaySortingRadioButtons();

    this->librarySummaryOutputLabel = new Fl_Output(190, 110, 0, 0, "Movie library summary:");

    this->summaryOutputTextBuffer = new Fl_Text_Buffer();
    this->summaryOutputTextDisplay = new Fl_Text_Display(20, 120, 500, 200);
    this->summaryOutputTextDisplay->textfont(FL_COURIER);
    this->summaryOutputTextDisplay->buffer(summaryOutputTextBuffer);

    this->loadButton = new Fl_Button(120, 330, 70, 30, "Load");
    this->loadButton->callback(cbLoad, this);

    this->saveButton = new Fl_Button(200, 330, 70, 30, "Save");
    this->saveButton->callback(cbSave, this);

    this->addButton = new Fl_Button(280, 330, 70, 30, "Add");
    this->addButton->callback(cbAddMovie, this);

    this->deleteButton = new Fl_Button(360, 330, 70, 30, "Delete");
    this->deleteButton->callback(cbDeleteMovie, this);

    this->movieList = new MovieList();

    end();
}

void MovieLibraryWindow::draw()
{
    Fl_Window::draw();
    fl_frame("AAAA", 20, 35, 500, 55);
}


void MovieLibraryWindow::createAndDisplaySortingRadioButtons()
{
    const int X_RADIO_GROUP = 35;
    const int Y_RADIO_GROUP = 45;
    const int WIDTH_RADIO_GROUP = 400;
    const int HEIGHT_RADIO_GROUP = 100;

    this->sortingRadioGroup = new Fl_Group(X_RADIO_GROUP, Y_RADIO_GROUP, WIDTH_RADIO_GROUP, HEIGHT_RADIO_GROUP);

    this->sortingRadioGroup->begin();

    for (int i = 0; i < SORTING_GROUPS; i++)
    {
        for (int j = 0; j < SORTING_TYPES_PER_GROUP; j++)
        {
            string label = this->sortingGroup[i] + " " + this->sortingTypes[j];
            int offset = (i*SORTING_TYPES_PER_GROUP) + j;
            this->radioSortingLabels[offset] = new string(label);
            this->sortingRadioGroupButton[offset] = new Fl_Round_Button(X_RADIO_GROUP + i*160, Y_RADIO_GROUP + j*25, 12, 12, radioSortingLabels[offset]->c_str());
            this->sortingRadioGroupButton[offset]->type(FL_RADIO_BUTTON);
            this->sortingRadioGroupButton[offset]->callback(cbSortingMethodChanged, this);
        }
    }

    this->sortingRadioGroup->end();

    this->sortingRadioGroupButton[0]->set();
    this->sortOrderSelection = NAME_ASCENDING;
}

void MovieLibraryWindow::cbSortingMethodChanged(Fl_Widget* widget, void* data)
{
    MovieLibraryWindow* window = (MovieLibraryWindow*)data;
    window->sortingMethodChanged();

#ifdef DIAGNOSTIC_OUTPUT
    cout << "Sorting method: " << window->getSortOrder() << endl;
#endif
}

void MovieLibraryWindow::sortingMethodChanged()
{
    setSortOrderBasedOnSelection();
    updateSummaryText();
}

//
// Callback when the Load button is invoked
//
// @precondition widget != 0 AND data != 0
// @postcondition MovieLibraryWindow::getFilename() == file selected by the user
//
// @param widget The widget that initiated the callback
// @param data Any data that was passed with the call back. In this instance, a pointer to the window.
//
void MovieLibraryWindow::cbLoad(Fl_Widget* widget, void* data)
{
    MovieLibraryWindow* window = (MovieLibraryWindow*)data;
    window->promptUserForFilename(Fl_File_Chooser::SINGLE, "Movie file to load");

#ifdef DIAGNOSTIC_OUTPUT
    cout << "Filename selected: " << window->getFilename() << endl;
#endif

    window->loadListFromFile();
    window->updateSummaryText();
}

const string MovieLibraryWindow::promptUserForFilename(int type, const string& title)
{
    Fl_File_Chooser chooser(".", "*", type, title.c_str());
    chooser.show();

    while(chooser.shown())
    {
        Fl::wait();
    }

    if (chooser.value() != 0)
    {
        this->selectedFilename = chooser.value();
    }
    else
    {
        this->selectedFilename = "";
    }

    return this->selectedFilename;
}

const std::string MovieLibraryWindow::getFilename() const
{
    return this->selectedFilename;
}

void MovieLibraryWindow::cbSave(Fl_Widget* widget, void* data)
{
    MovieLibraryWindow* window = (MovieLibraryWindow*)data;
    window->promptUserForFilename(Fl_File_Chooser::CREATE, "Movie file to save to");

#ifdef DIAGNOSTIC_OUTPUT
    cout << "Filename selected: " << window->getFilename() << endl;
#endif

    window->saveListToFile();
}

void MovieLibraryWindow::loadListFromFile()
{
    if (this->selectedFilename != "")
    {
        delete this->movieList;
        this->movieList = loadMoviesFromFile(this->selectedFilename);
    }
}

void MovieLibraryWindow::saveListToFile()
{
    writeMoviesToFile(this->selectedFilename, this->movieList);
}

void MovieLibraryWindow::cbAddMovie(Fl_Widget* widget, void* data)
{
    MovieLibraryWindow* window = (MovieLibraryWindow*)data;

    AddMovieWindow addMovie;
    addMovie.set_modal();
    addMovie.show();

    while (addMovie.shown())
    {
        Fl::wait();
    }

    if (addMovie.getWindowResult() == OKCancelWindow::WindowResult::OK)
    {
        Movie* movie = addMovie.getMovie();
#ifdef DIAGNOSTIC_OUTPUT
        cout << "OK" << endl;
        cout << "Name: " << movie->getName() << endl;
        cout << "Studio: " << movie->getStudio() << endl;
        cout << "Year: " << movie->getYear() << endl;
        cout << "Rating: " << movie->getRating() << endl;
        cout << "Length: " << movie->getLength() << endl;
#endif
        window->addMovie(movie);
        window->updateSummaryText();
    }
#ifdef DIAGNOSTIC_OUTPUT
    else
    {
        cout << "Cancel or closed window." << endl;
    }
#endif

}

void MovieLibraryWindow::cbDeleteMovie(Fl_Widget* widget, void* data)
{
    MovieLibraryWindow* window = (MovieLibraryWindow*)data;

    DeleteMovieWindow deleteMovie;
    deleteMovie.set_modal();
    deleteMovie.show();

    while (deleteMovie.shown())
    {
        Fl::wait();
    }


    if (deleteMovie.getWindowResult() == OKCancelWindow::WindowResult::OK)
    {
        bool movieRemoved = window->deleteMovie(deleteMovie.getName());
        window->updateSummaryText();
#ifdef DIAGNOSTIC_OUTPUT
        std::cout << "OK - Movie name: " << deleteMovie.getName() << std::endl;
        if (movieRemoved)
        {
            std::cout << "The movie was found and removed" << std::endl;
        }
        else
        {
            std::cout << "The movie was not found" << std::endl;
        }
#endif
    }
#ifdef DIAGNOSTIC_OUTPUT
    else
    {
        std::cout << "Cancel or closed window." << std::endl;
    }
#endif

}

void MovieLibraryWindow::addMovie(Movie* movie)
{
    this->movieList->insertMovie(movie);
}

bool MovieLibraryWindow::deleteMovie(const std::string& movieName)
{
    return this->movieList->removeMovie(movieName);
}

void MovieLibraryWindow::setSortOrderBasedOnSelection()
{
    for (int i = 0; i < TOTAL_SORTING_METHODS; i++)
    {
        if (this->sortingRadioGroupButton[i]->value())
        {
            this->sortOrderSelection = (SortOrder)i;
        }
    }
}

void MovieLibraryWindow::updateSummaryText()
{
    setSummaryText(this->movieList->getOutputDisplay(this->sortOrderSelection));
}

void MovieLibraryWindow::setSummaryText(const std::string& outputText)
{
    this->summaryOutputTextBuffer->text(outputText.c_str());
}

SortOrder MovieLibraryWindow::getSortOrder() const
{
    return this->sortOrderSelection;
}

MovieLibraryWindow::~MovieLibraryWindow()
{
    for (int i = 0; i < TOTAL_SORTING_METHODS; i++)
    {
        delete this->radioSortingLabels[i];
        delete this->sortingRadioGroupButton[i];
    }

    delete this->sortingOutputLabel;

    delete this->librarySummaryOutputLabel;
    this->summaryOutputTextDisplay->buffer(0);
    delete this->summaryOutputTextBuffer;
    delete this->summaryOutputTextDisplay;

    delete this->loadButton;
    delete this->saveButton;
    delete this->addButton;
    delete this->deleteButton;

    delete this->movieList;
}

}
