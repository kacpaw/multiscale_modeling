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
void addColors(std::map<int, nana::color>& colors, int n);

int main() {

	int width, height;
	sizeForm(&width, &height);
	mainForm2(width, height);
}



void mainForm2(int width, int height) {

	nana::form form;
	form.size(nana::size(width + 350, height));

	nana::button resize_button(form);
	resize_button.caption("resize");
	resize_button.events().click([&](const nana::arg_click& a_m)
		{
			form.close();
			int width, height;
			sizeForm(&width, &height);
			mainForm(width, height);

		});


	nana::button start_random_board(form);
	start_random_board.caption("generate MC");
	nana::textbox ids_count(form);
	ids_count.caption("20");
	nana::label ids_count_label(form);
	ids_count_label.caption("Amount of States");


	nana::button start_mc(form);
	start_mc.caption("Simulate MC");
	nana::textbox steps_count(form);
	steps_count.caption("10");
	nana::label steps_count_label(form);
	steps_count_label.caption("Amount of MC steps");


	nana::combox selection_type(form);
	nana::button selection_button(form);
	selection_type.push_back("SUB");
	selection_type.push_back("DP");
	selection_type.push_back("boundaries");
	selection_type.push_back("boundaries (all)");
	selection_button.caption("go");



	nana::button nucleins_button(form);
	nucleins_button.caption("add");
	nana::label grains_number_label(form);
	grains_number_label.caption("number of grains");
	nana::textbox grains_number_input(form);

	nana::button start_button(form);
	nana::combox grow_type(form);
	nana::textbox propability_input(form);
	grow_type.push_back("simple grow");
	grow_type.push_back("with grain curvature");
	start_button.caption("start");
	propability_input.caption("90");


	nana::label inside_label(form);
	nana::label on_edge_label(form);
	inside_label.caption("E inside");
		on_edge_label.caption("E on edge");
	nana::textbox energy_on_edges(form);
	energy_on_edges.caption("8");
	nana::textbox energy_inside(form);
	energy_inside.caption("5");
	nana::button start_ed(form);
	start_ed.caption("show energy");
	nana::combox ed_type(form);
	ed_type.push_back("Homogenous");
	ed_type.push_back("Heterogenous");


	nana::combox nucleation_type1(form);
	nucleation_type1.push_back("constant");
	nucleation_type1.push_back("increasing");
	nucleation_type1.push_back("begining");
	nana::combox nucleation_type2(form);
	nucleation_type2.push_back("boundaries");
	nucleation_type2.push_back("anywhere");
	nana::button start_recrystalization(form);
	start_recrystalization.caption("start recrystalization");


	nana::textbox recrystalization_steps(form);
	recrystalization_steps.caption("5");
	nana::label recrystalization_steps_label(form);
	recrystalization_steps_label.caption("steps");

	nana::textbox amount_of_nucleons(form);
	amount_of_nucleons.caption("20");
	nana::label amount_of_nucleons_label(form);
	amount_of_nucleons_label.caption("amount");
	nana::place layout(form);

	//layout.div("<weight=60% canvas><vertical<weight=30 resize><weight=30 ids_number><weight=30><weight=30 add_grains><vertical weight=50 options><weight=30 start><weight=30 select><weight=30 io><weight=30 energy1><weight=30 energy2><weight=30 nucleation>>");
	layout.div("<weight=60% canvas><vertical<weight =30 grains_number><weight =30 grow><weight =50 modificatoions margin=[20]><weight =50 mc_states margin=[20]><weight =30 mc_steps><weight =30 mc_start><weight =50 energy_distribution_parameters margin=[20]><weight =30 energy_distribution_type><weight =50 nucleation_type margin=[20]><weight =30 nucleation_parameters><weight =30 nucleation_start>>");

	layout["grains_number"] << grains_number_label << grains_number_input << nucleins_button;
	layout["grow"] << grow_type << propability_input << start_button;
	layout["modificatoions"] << selection_type << selection_button;
	layout["mc_states"] << ids_count_label << ids_count;
	layout["mc_steps"] << steps_count_label << steps_count;
	layout["mc_start"] << start_mc << start_random_board;
	layout["energy_distribution_parameters"] << inside_label << energy_inside << on_edge_label << energy_on_edges;;
	layout["energy_distribution_type"] << start_ed << ed_type;
	layout["nucleation_type"] << nucleation_type1 << nucleation_type2;
	layout["nucleation_parameters"] << recrystalization_steps_label << recrystalization_steps << amount_of_nucleons_label << amount_of_nucleons;
	layout["nucleation_start"] << start_recrystalization;


	//layout["ids_number"] << grains_number_label << grains_number_input << nucleins_button;
	//layout["add_grains"] << grow_type << propability_input << start_button;
	//layout["start"] << ids_count << start_random_board;
	//layout["io"] << steps_count << start_mc;
	//layout["select"] << selection_type << selection_button;
	//layout["energy1"] << inside_label << energy_inside << on_edge_label << energy_on_edges;
	//layout["energy2"] << start_ed << ed_type;
	//layout["nucleation"] << start_recrystalization;

	layout.collocate();


	GrainsBoard *board = new GrainsBoard(width, height);
	nana::paint::graphics graph(nana::size(width, height *2 +10));

	nana::drawing dw(form);
	dw.draw([&](nana::paint::graphics& gr) {
		gr.bitblt(nana::rectangle(0, 0, width, height*2+10), graph);
		});

	std::map<int, nana::color> colors;
	std::map<int, nana::color> colors2;
	nana::color white = white.from_rgb(255, 255, 255);
	nana::color black = black.from_rgb(0, 0, 0);
	colors[0] = white;
	colors[-1] = black;

	std::list<int>selected;
	std::list<int>ignore;



	start_recrystalization.events().click([&](const nana::arg_click& a_m)
		{
			start_recrystalization.enabled(false);
			int amount = std::stoi(amount_of_nucleons.caption());
			//board->srxmc_add_nucleons(10);

			int n = 50;

			if (colors2.size() < amount)
			{
				while(colors2.size()<amount)
				{
					int r = rand() % 255;

					nana::color col = col.from_rgb(r, 0, 0);

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
						continue;
					}
					colors2[-1-colors2.size()] = col;
				}
			}
			board->srxmc(10);

			int steps = std::stoi(recrystalization_steps.caption());

			if (nucleation_type1.caption() == "begining")
			{
				board->srxmc_add_nucleons(amount,0);
				for (int i = 0; i < steps; i++)
				{
					board->srxmc(0);
				}
			}
			else if (nucleation_type1.caption() == "constant")
			{
				int d = amount / steps;
				for (int i = 0; i < steps; i++)
				{
					board->srxmc_add_nucleons(d, 0);
					board->srxmc(0);
				}

			}
			else
			{

			}
	

			int** b = board->getBoard();
			for (int y = 0; y < height; y++)
			{
				for (int x = 0; x < width; x++)
				{
					if(b[y][x]>-1)
						graph.set_pixel(x, y, colors[b[y][x]]);
					else
						graph.set_pixel(x, y, colors2[b[y][x]]);
				}
				delete b[y];
			}
			delete b;

			
			double** c = board->getEnergy();
			for (int y = 0; y < height; y++)
			{
				for (int x = 0; x < width; x++)
				{
					graph.set_pixel(x, y + width + 10, nana::color(int((c[y][x] / 10) * 255), 0, 0));
				}
				delete c[y];
			}
			delete c;
						
			dw.update();

			start_recrystalization.enabled(true);

		});



	start_ed.events().click([&](const nana::arg_click& a_m)
		{
			double ee = std::stoi(energy_on_edges.caption());
			double ei = std::stoi(energy_inside.caption());

			if (ed_type.caption() == "Homogenous")
			{
				board->distributeEnergy(energyDistributionType::HOMOGENOUS, ei);
			}
			else
			{
				board->distributeEnergy(energyDistributionType::HETEROGENOUS, ei, ee);
			}

			double max_energy;
			if (ee > ei)
			{
				max_energy = ee + 0.1 * ee;
			}
			else
			{
				max_energy = ei + 0.1 * ei;
			}
			double** b = board->getEnergy();
			for (int y = 0; y < height; y++)
			{
				for (int x = 0; x < width; x++)
				{
					graph.set_pixel(x, y+width + 10, nana::color(int((b[y][x] / max_energy) * 255), 0, 0));
				}
				delete b[y];
			}
			delete b;

			dw.update();
		});


	selection_button.events().click([&](const nana::arg_click& a_m)
		{
			if (selection_type.caption() == "SUB")
			{
				board->clear(selected);
			}
			else if (selection_type.caption() == "boundaries")
			{
				board->selectedBoundaries(selected);
			}
			else if (selection_type.caption() == "boundaries (all)") {
				board->allBoundaries();
			}
			else
			{
				board->setNewColor(selected);
				board->clear(selected);
			}
			ignore = selected;
			selected.clear();

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
		});



	start_random_board.events().click([&](const nana::arg_click& a_m)
		{
			start_random_board.enabled(false);


			int n = std::stoi(ids_count.caption());
			board->fillRandomly(ignore, n);
			
			if (colors.size() -2 < n)
			{
				addColors(colors, n - colors.size() + 2);
			}


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
			start_random_board.enabled(true);

		});


	start_mc.events().click([&](const nana::arg_click& a_m)
		{
			start_mc.enabled(false);

			for (int i = 0; i < std::stoi(steps_count.caption()); i++)
			{
				board->mc_method(100000);
			}

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

			start_mc.enabled(true);

		});


	form.events().mouse_down([&](const nana::arg_mouse& arg)
		{
			if ((arg.pos.x < width) && (arg.pos.x < height))
			{
				int** b = board->getBoard();
				selected.push_back(board->get(arg.pos.x, arg.pos.y));
				std::cout << arg.pos.x << " " << arg.pos.y << std::endl;
			}

		});



	nucleins_button.events().click([&](const nana::arg_click& a_m)
		{
			nucleins_button.enabled(false);
			std::string caption = grains_number_input.caption();
			int grains_number = std::stoi(caption);

			board->addNucleons(grains_number);

			srand(time(NULL));

			int s = colors.size() - 1;
			for (int i = s; i < s + grains_number; i++)
			{
				std::cout << colors.size() << std::endl;
				int r = rand() % 255;
				int g = rand() % 255;
				int b = rand() % 255;
				nana::color col = col.from_rgb(0, g, b);

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
			nucleins_button.enabled(true);

		});


	start_button.events().click([&](const nana::arg_click& a_m)
		{
			start_button.enabled(false);


			if (grow_type.caption() == "simple grow")
			{
				board->grow(growthType::SIMPLE_GROWTH, 100, 100, ignore);
			}
			else
			{
				std::string caption = propability_input.caption();
				int propability = std::stoi(caption);
				board->grow(growthType::CURVATURE_GROWTH, 1000, propability, ignore);
			}


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

			selection_button.enabled(true);
			selection_type.enabled(true);
			start_button.enabled(true);

		});



	form.show();
	nana::exec();
}



void addColors(std::map<int, nana::color>& colors, int n) {


	int s = colors.size() - 1;
	for (int i = 0; i < n; i++)
	{
		std::cout << colors.size() << std::endl;
		int r = rand() % 255;
		int g = rand() % 255;
		int b = rand() % 255;
		nana::color col = col.from_rgb(0, g, b);

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
		colors[colors.size()-1] = col;
	}

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