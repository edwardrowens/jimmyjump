#include "TheGame.h"
#include "LineCalculationService.h"

int main(int argc, char** argv){
	Point p1 = Point(0, 0);
	Point p2 = Point(4, 4);

	Point p3 = Point(1, 1);
	Point p4 = Point(1, 4);

	Line line1 = Line(p1, p2);
	Line line2 = Line(p3, p4);

	Point p5 = LineCalculationService::intersectionOfTwoLines(line1, line2);

	/*TheGame game;
	game.run();*/

	return 0;
}