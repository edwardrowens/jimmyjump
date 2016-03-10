#include "TheGame.h"
#include "LineCalculationService.h"

int main(int argc, char** argv){
	Point p1 = Point(5, 1);
	Point p2 = Point(1, 8);

	Point p3 = Point(3, 4);
	Point p4 = Point(6, 20);

	Line line1 = Line(p1, p2);
	Line line2 = Line(p3, p4);

	Point p5 = LineCalculationService::intersectionOfTwoLines(line1, line2);

	/*TheGame game;
	game.run();*/

	return 0;
}