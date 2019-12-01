#include <iostream>
#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/combox.hpp>
#include <nana/gui/widgets/checkbox.hpp >
#include <dlib/image_io.h>
#include <nana/gui/filebox.hpp>

#include "../staticLib/GrainsBoard.h"


void mainForm(int width, int height);
void mainForm2(int width, int height);
void sizeForm(int* width, int* height);

int main() {

	int width, height;
	sizeForm(&width, &height);
	mainForm2(width, height);
}




void mainForm2(int width, int height) {

	nana::form form;

	nana::button resize_button(form);
	resize_button.caption("resize");
	resize_button.events().click([&](const nana::arg_click& a_m)
		{
			form.close();
			int width, height;
			sizeForm(&width, &height);
			mainForm(width, height);

		});

	nana::button start_button(form);
	nana::combox grow_type(form);
	nana::textbox propability_input(form);
	grow_type.push_back("simple grow");
	grow_type.push_back("with grain curvature");
	start_button.caption("start");
	propability_input.caption("90");


	nana::button nucleins_button(form);
	nucleins_button.caption("add");
	nana::label grains_number_label(form);
	grains_number_label.caption("number of grains");

	nana::textbox grains_number_input(form);

	nana::button inclusions_button(form);
	nana::textbox inclusions_number_input(form);
	nana::textbox inclusions_size_input(form);
	nana::label inclusions_number_label(form);
	nana::label inclusions_size_label(form);
	inclusions_button.caption("add");
	inclusions_number_label.caption("number of inclusions");
	inclusions_size_label.caption("size of inclusions");
	nana::combox inclusions_type(form);
	inclusions_type.push_back("square");
	inclusions_type.push_back("circle");

	nana::button clear_button(form);
	clear_button.caption("clear");

	nana::combox selection_type(form);
	nana::button selection_button(form);
	selection_type.push_back("SUB");
	selection_type.push_back("DP");
	selection_type.push_back("boundaries");
	selection_type.push_back("boundaries (all)");
	selection_button.caption("go");


	selection_button.enabled(false);
	selection_type.enabled(false);


	form.size(nana::size(width + 250, height));

	nana::place layout(form);

	layout.div("<weight=60% canvas><vertical<weight=30 resize><weight=30 ids_number><weight=30 inclusions_type><weight=30 inclusions_number><vertical weight=50 options><weight=30 start><weight=30 select><io>>");

	layout["resize"] << resize_button;
	layout["ids_number"] << grains_number_label << grains_number_input << nucleins_button;
	layout["start"] << start_button;
	


	layout.collocate();


	GrainsBoard *board = new GrainsBoard(width, height);
	nana::paint::graphics graph(nana::size(width, height));
	nana::drawing dw(form);
	dw.draw([&](nana::paint::graphics& gr) {
		gr.bitblt(nana::rectangle(0, 0, width, height), graph);
		});

	std::map<int, nana::color> colors;
	nana::color white = white.from_rgb(255, 255, 255);
	nana::color black = black.from_rgb(0, 0, 0);
	colors[0] = white;
	colors[-1] = black;

	std::list<int>selected;
	std::list<int>ignore;





	start_button.events().click([&](const nana::arg_click& a_m)
		{
			start_button.enabled(false);

			delete board;

			board = new GrainsBoard(width, height, stoi(grains_number_input.caption()));
			


			int** b = board->getBoard();
			for (int y = 0; y < height; y++)
			{
				for (int x = 0; x < width; x++)
				{
					graph.set_pixel(x, y, colors[b[y][x]]);
				}
				delete b[y];
			}
			delete b;

			dw.update();
			start_button.enabled(true);

		});





	form.show();
	nana::exec();
}




void mainForm(int width, int height) {

	nana::form form;

	nana::button resize_button(form);
	resize_button.caption("resize");
	resize_button.events().click([&](const nana::arg_click& a_m)
	{
		form.close();
		int width, height;
		sizeForm(&width, &height);
		mainForm(width, height);

	});

	nana::button start_button(form);
	nana::combox grow_type(form);
	nana::textbox propability_input(form);
	grow_type.push_back("simple grow");
	grow_type.push_back("with grain curvature");
	start_button.caption("start");
	propability_input.caption("90");


	nana::button nucleins_button(form);
	nucleins_button.caption("add");
	nana::label grains_number_label(form);
	grains_number_label.caption("number of grains");
	
	nana::textbox grains_number_input(form);

	nana::button inclusions_button(form);
	nana::textbox inclusions_number_input(form);
	nana::textbox inclusions_size_input(form);
	nana::label inclusions_number_label(form);
	nana::label inclusions_size_label(form);
	inclusions_button.caption("add");
	inclusions_number_label.caption("number of inclusions");
	inclusions_size_label.caption("size of inclusions");
	nana::combox inclusions_type(form);
	inclusions_type.push_back("square");
	inclusions_type.push_back("circle");

	nana::button clear_button(form);
	clear_button.caption("clear");

	nana::combox selection_type(form);
	nana::button selection_button(form);
	selection_type.push_back("SUB");
	selection_type.push_back("DP");
	selection_type.push_back("boundaries");
	selection_type.push_back("boundaries (all)");
	selection_button.caption("go");


	selection_button.enabled(false);
	selection_type.enabled(false);


	form.size(nana::size(width+250, height));

	nana::place layout(form);

	layout.div("<weight=60% canvas><vertical<weight=30 resize><weight=30 grains_number><weight=30 inclusions_type><weight=30 inclusions_number><vertical weight=50 options><weight=30 start><weight=30 select><io>>");

	layout["resize"] << resize_button;
	layout["grains_number"] << grains_number_label << grains_number_input << nucleins_button;
	layout["start"] << grow_type << propability_input << start_button;
	layout["inclusions_type"]  << inclusions_size_label << inclusions_size_input << inclusions_type;
	layout["inclusions_number"] << inclusions_number_label << inclusions_number_input << inclusions_button;
	layout["select"] << selection_type << selection_button;



	layout.collocate();


	GrainsBoard board(width, height);
	nana::paint::graphics graph(nana::size(width, height));
	nana::drawing dw(form);
	dw.draw([&](nana::paint::graphics& gr) {
		gr.bitblt(nana::rectangle(0, 0, width, height), graph);
	});

	std::map<int, nana::color> colors;
	nana::color white = white.from_rgb(255, 255, 255);
	nana::color black = black.from_rgb(0, 0, 0);
	colors[0] = white;
	colors[-1] = black;

	std::list<int>selected;
	std::list<int>ignore;

	nucleins_button.events().click([&](const nana::arg_click& a_m)
	{
		nucleins_button.enabled(false);
		std::string caption = grains_number_input.caption();
		int grains_number = std::stoi(caption);

		board.addNucleons(grains_number);

		srand(time(NULL));

		int s = colors.size() - 1;
		for (int i = s; i < s +grains_number; i++)
		{
			std::cout << colors.size() << std::endl;
			int r = rand() % 255;
			int g = rand() % 255;
			int b = rand() % 255;
			nana::color col = col.from_rgb(r, g, b);
			
			bool isColor = false;
			for (auto color : colors)
			{
				if (color.second == col) {
					isColor = true;
					break;
				}
			}

			if (isColor)
			{
				i--;
				continue;
			}
			colors[i] = col;
		}

		int** b = board.getBoard();
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				graph.set_pixel(x, y, colors[b[y][x]]);
			}
			delete b[y];
		}
		delete b;
		dw.update();
		nucleins_button.enabled(true);

	});


	start_button.events().click([&](const nana::arg_click& a_m)
		{
			start_button.enabled(false);


			if (grow_type.caption() == "simple grow")
			{
				board.grow(growthType::SIMPLE_GROWTH, 1000, 100, ignore);
			}
			else
			{
				std::string caption = propability_input.caption();
				int propability = std::stoi(caption);
				board.grow(growthType::CURVATURE_GROWTH, 1000, propability, ignore);
			}


				int** b = board.getBoard();
				for (int y = 0; y < height; y++)
				{
					for (int x = 0; x < width; x++)
					{
						graph.set_pixel(x, y, colors[b[y][x]]);
					}
					delete b[y];
				}
				delete b;

				dw.update();

			selection_button.enabled(true);
			selection_type.enabled(true);
			start_button.enabled(true);

		});


	inclusions_button.events().click([&](const nana::arg_click& a_m)
		{
			nucleins_button.enabled(false);
			std::string caption = inclusions_number_input.caption();
			int inclusions_number = std::stoi(caption);

			caption = inclusions_size_input.caption();
			int inclusions_size = std::stoi(caption);

			if (inclusions_type.caption() == "square")
			{
				board.addInclusions(inclusionsType::SQUARE, inclusions_size, inclusions_number);
			}
			else
			{
				board.addInclusions(inclusionsType::CIRCLE, inclusions_size, inclusions_number);
			}

			int** b = board.getBoard();
			for (int y = 0; y < height; y++)
			{
				for (int x = 0; x < width; x++)
				{
					graph.set_pixel(x, y, colors[b[y][x]]);
				}
				delete b[y];
			}
			delete b;

			dw.update();
			nucleins_button.enabled(true);

		});

	selection_button.events().click([&](const nana::arg_click& a_m)
	{
		if (selection_type.caption() == "SUB")
		{
			board.clear(selected);
		}
		else if (selection_type.caption() == "boundaries")
		{
			board.selectedBoundaries(selected);
		}
		else if (selection_type.caption() == "boundaries (all)") {
			board.allBoundaries();
		}
		else
		{

		}
		ignore = selected;
		selected.clear();

		int** b = board.getBoard();
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				graph.set_pixel(x, y, colors[b[y][x]]);
			}
			delete b[y];
		}
		delete b;

		dw.update();
	});


	form.events().mouse_down([&](const nana::arg_mouse& arg)
		{
			if ((arg.pos.x < width) && (arg.pos.x < height))
			{
				int** b = board.getBoard();
				selected.push_back(board.get(arg.pos.x, arg.pos.y));
				std::cout << arg.pos.x << " " << arg.pos.y << std::endl;
			}

		});


	form.show();
	nana::exec();
}



void sizeForm(int* width, int* height) {

	std::shared_ptr<nana::form> form = std::make_shared<nana::form>();
	form->size(nana::size(300, 180));
	form->caption("size");

	std::shared_ptr<nana::label> width_label = std::make_shared <nana::label>(*form, nana::rectangle(50, 10, 200, 30));
	std::shared_ptr<nana::label> height_label = std::make_shared <nana::label>(*form, nana::rectangle(50, 70, 200, 30));

	std::shared_ptr<nana::textbox> width_textbox = std::make_shared <nana::textbox>(*form, nana::rectangle(50, 40, 200, 30));
	std::shared_ptr<nana::textbox> height_textbox = std::make_shared <nana::textbox>(*form, nana::rectangle(50, 100, 200, 30));

	std::shared_ptr<nana::button> btn = std::make_shared <nana::button>(*form, nana::rectangle(50, 140, 200, 30));;


	width_label->caption("width");
	width_label->text_align(nana::align::center, nana::align_v::center);

	height_label->caption("height");
	height_label->text_align(nana::align::center, nana::align_v::center);

	width_textbox->caption("300");
	width_textbox->text_align(nana::align::center);

	height_textbox->caption("300");
	height_textbox->text_align(nana::align::center);

	btn->caption("OK");
	btn->events().click([&](const nana::arg_click& a_m)
		{
			*width = std::stoi(width_textbox->caption());
			*height = std::stoi(height_textbox->caption());
			form->close();
		});

	form->show();
	nana::exec();
}