#ifndef MOVIELIBRARYWINDOW_H
#define MOVIELIBRARYWINDOW_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Button.H>

#include <vector>
#include <string>

#include "../model/MovieList.h"
#include "../utils/Utils.h"

using namespace model;

namespace view
{

/**
 *  Defines the window where a user can load, save, add, and delete movies from a movie library.
 */
class MovieLibraryWindow : public Fl_Window
{
public:
    /**
     *  Constructs a movie library window creating and initializing all the widgets that will be displayed.
     *
     *  @precondition width > 0 AND height > 0
     *  @postcondition Window is constructed
     *
     *  @param width The width of the window
     *  @param height The height of the window
     *  @param title The title to display for the window
     */
    MovieLibraryWindow(int width, int height, const char* title);
    /**
     * Destructor.
     */
    virtual ~MovieLibraryWindow();

private:
    static const int SORTING_GROUPS = 3;
    static const int SORTING_TYPES_PER_GROUP = 2;
    static const int TOTAL_SORTING_METHODS = SORTING_GROUPS * SORTING_TYPES_PER_GROUP;

    std::vector<std::string> sortingGroup = {"Name", "Rating", "Length"};
    std::vector<std::string> sortingTypes = {"Ascending", "Descending"};
    std::string* radioSortingLabels[TOTAL_SORTING_METHODS];

    Fl_Output *sortingOutputLabel;
    Fl_Group *sortingRadioGroup;
    Fl_Round_Button *sortingRadioGroupButton[TOTAL_SORTING_METHODS];
    SortOrder sortOrderSelection;

    Fl_Output *librarySummaryOutputLabel;

    Fl_Text_Buffer *summaryOutputTextBuffer;
    Fl_Text_Display *summaryOutputTextDisplay;

    Fl_Button* loadButton;
    Fl_Button* saveButton;
    Fl_Button* addButton;
    Fl_Button* deleteButton;

    std::string selectedFilename;

    MovieList* movieList;

    void createAndDisplaySortingRadioButtons();
    void setSortOrderBasedOnSelection();
    void updateSummaryText();
    void loadListFromFile();
    void saveListToFile();
    void addMovie(Movie* movie);
    bool deleteMovie(const std::string& movieName);

    void draw();

    static void cbSortingMethodChanged(Fl_Widget* widget, void* data);
    void sortingMethodChanged();

    static void cbLoad(Fl_Widget* widget, void* data);
    static void cbSave(Fl_Widget* widget, void* data);
    const std::string promptUserForFilename(int type, const std::string& title);
    const std::string getFilename() const;

    static void cbAddMovie(Fl_Widget* widget, void* data);
    static void cbDeleteMovie(Fl_Widget* widget, void* data);

    SortOrder getSortOrder() const;

    void setSummaryText(const std::string& outputText);
};

} // namespace view

#endif // MOVIELIBRARYWINDOW_H
