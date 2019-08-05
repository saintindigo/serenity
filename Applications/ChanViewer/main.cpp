#include "BoardListModel.h"
#include "ThreadCatalogModel.h"
#include <LibDraw/PNGLoader.h>
#include <LibGUI/GApplication.h>
#include <LibGUI/GBoxLayout.h>
#include <LibGUI/GComboBox.h>
#include <LibGUI/GTableView.h>
#include <LibGUI/GWindow.h>

int main(int argc, char** argv)
{
    GApplication app(argc, argv);

    auto* window = new GWindow;
    window->set_title("ChanViewer");
    window->set_rect(100, 100, 800, 500);
    window->set_icon(load_png("/res/icons/16x16/app-chanviewer.png"));

    auto* widget = new GWidget;
    window->set_main_widget(widget);
    widget->set_fill_with_background_color(true);
    widget->set_layout(make<GBoxLayout>(Orientation::Vertical));

    auto* board_combo = new GComboBox(widget);
    board_combo->set_only_allow_values_from_model(true);
    board_combo->set_size_policy(SizePolicy::Fill, SizePolicy::Fixed);
    board_combo->set_preferred_size(0, 20);
    board_combo->set_model(BoardListModel::create());

    auto* catalog_view = new GTableView(widget);
    catalog_view->set_model(ThreadCatalogModel::create());

    board_combo->on_change = [&] (auto&, const GModelIndex& index) {
        auto selected_board = board_combo->model()->data(index, GModel::Role::Custom);
        ASSERT(selected_board.is_string());
        static_cast<ThreadCatalogModel*>(catalog_view->model())->set_board(selected_board.to_string());
    };

    window->show();

    return app.exec();
}