#ifndef NCURSES_APPLICATION_BINDINGS_H_
#define NCURSES_APPLICATION_BINDINGS_H_

#include "ncf/ncurses/Window.hpp"
#include "ncf/Widget.hpp"
#include "ncf/Component.hpp"
#include "common/Arguments.hpp"

#include <curses.h>
#include <cassert>
#include <vector>

//TODO: Create a pointer/unique_ptr/object to stdscr window that is const and unmovable.

namespace ncf {

struct Colors {
    ncurses::ColorPair ColorPair1;
    ncurses::ColorPair ColorPair2;
    ncurses::ColorPair ColorPair3;
    ncurses::ColorPair ColorPair4;
    ncurses::ColorPair ColorPair5;
    ncurses::ColorPair ColorPair6;
};

struct Attributes {
    short cursorVisibility;
    Colors colors;
};

class Application {
    public:
        /**
         * Application Constructor
         *
         * @param enableColors enables use of colors
         */
        explicit Application(bool enableColors = true);

        /**
         * Application Constructor
         *
         * @param args         command line arguments
         * @param enableColors enables use of colors
         */
        Application(Arguments args, bool enableColors = true);

        /**
         * Application Destructor
         */
        virtual ~Application();

        /**
         * Start the Application
         */
        virtual void start();

        inline void setInitialContext(Widget* widget)
        {
            assert(widget != NULL);
            m_currWdgtWithFocus = widget;
        }

        //void setController(std::unique_ptr<Controller> controller);

        void setKillKey(char key)
        {
            //TODO: Check for key binding conflicts
            m_killKey = key;
        }

        char killKey()
        {
            return m_killKey;
        }

        /**
         * Attributes to use for menu and forms foregrounds
         *
         * @return default foreground attributes
         */
        virtual ncurses::NCCharType foregrounds() const {
            return m_hasColors ? static_cast<ncurses::NCCharType>(COLOR_PAIR(1)) : A_BOLD;
        }

        /**
         * Attributes to use for menu and forms backgrounds
         *
         * @return default background attributes
         */
        virtual ncurses::NCCharType backgrounds() const {
            return m_hasColors ? static_cast<ncurses::NCCharType>(COLOR_PAIR(2)) : A_NORMAL;
        }

        /**
         * Attributes to use for inactive (menu) elements
         *
         * @return default inactive attributes
         */
        virtual ncurses::NCCharType inactives() const {
            return m_hasColors ? static_cast<ncurses::NCCharType>(COLOR_PAIR(3)|A_DIM) : A_DIM;
        }

        /**
         * Attributes to use for (form) labels and SLKs
         *
         * @return default label attributes
         */
        virtual ncurses::NCCharType labels() const {
            return m_hasColors ? static_cast<ncurses::NCCharType>(COLOR_PAIR(4)) : A_NORMAL;
        }

        /**
         * Attributes to use for form backgrounds
         *
         * @return default form backgrounds
         */
        virtual ncurses::NCCharType dialogBackgrounds() const {
            return m_hasColors ? static_cast<ncurses::NCCharType>(COLOR_PAIR(4)) : A_NORMAL;
        }

        /**
         * Attributes to use as default for (form) window backgrounds
         *
         * @return default window backgrounds
         */
        virtual ncurses::NCCharType windowBackgrounds() const {
            return m_hasColors ? static_cast<ncurses::NCCharType>(COLOR_PAIR(5)) : A_NORMAL;
        }

        /**
         * Attributes to use for the title window
         *
         * @return default title window attributes
         */
        virtual ncurses::NCCharType screenTitles() const {
            return m_hasColors ? static_cast<ncurses::NCCharType>(COLOR_PAIR(6)) : A_BOLD;
        }

        /**
         * Get the Application instance
         *
         * @return the application instance
         */
        static Application* getApplication();

    private:
        /**
         * The unique Application instance
         */
        static Application* m_instance;

        Widget* m_currWdgtWithFocus = nullptr;
        bool m_hasColors = true;
        char m_killKey = 'q';
};

}
#endif
