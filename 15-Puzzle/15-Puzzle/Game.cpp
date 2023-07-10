#include "iostream"
#include "iomanip"
using namespace std;
constexpr int g_consoleLines{ 25 }; //To print some empty line 
static int moves{ 0 }; //Count moves have made

class cDirection {
public:
	//Enum to make sure only these type is valid
	enum Type {
		up, down, left, right
	};

	cDirection(Type type)
		:direction{ type }
	{}

	Type getType() const{
		return direction;
	}

	cDirection operator-() {
		switch (direction) {
		case up:
			return cDirection{ down };
		case down:
			return cDirection{ up };
		case left:
			return cDirection{ right };
		case right:
			return cDirection{ left };
		}
		cout << "Unsupported direction was passed!" << endl;
		return cDirection{ up };
	}

	friend ostream& operator << (ostream& os, const cDirection& dr) {
		switch (dr.direction) {
		case up:
			os << "up";
			return os;
		case down:
			os << "down";
			return os;
		case right:
			os << "right";
			return os;
		case left:
			os << "left";
			return os;
		default:
			os << "unknown";
			return os;
		}
	}

	static cDirection Instruction() {
		static int temp = 0;	//We use static here so the temp would not be init again everytime
		Type random = static_cast<Type>(temp);	//We use static_cast to convert from int to Type.
		temp++;
		return cDirection{ random };
	}

	static cDirection getRandomDirection() {
		Type random = static_cast<Type>(rand() % 4);	//We use static_cast to convert from int to Type.
		return cDirection{ random };
	}

private:
	Type direction;
};

//To help index the board since it is a 2D matrix
struct Point {
public:
	int x;
	int y;

	bool operator==(const Point& z) {
		return (x == z.x && y == z.y);
	}

	bool operator!= (const Point& z) {
		return !(*this == z);
	}

	Point getAdjacentDirection(const cDirection& temp) {
		switch (temp.getType()) {
			case cDirection::up:
				return Point{ x-1,y  };
			case cDirection::down:
				return Point{ x+1, y };
			case cDirection::right:
				return Point{ x,y+1 };
			case cDirection::left:
				return Point{ x,y-1 };
			default:
				return *this;
		}
	}
};


namespace UserInput {
	bool isValidCommand(char x) {
		return x == 'w' || x == 'a' || x == 's' || x == 'd' || x == 'q';
	}

	char getCharacter() {
		char ch;
		cout << "Input command: ";
		cin >> ch;
		cin.ignore();
		return ch;
	}

	char getCommandFromUser() {
		char ch{};
		while (!isValidCommand(ch))
			ch = getCharacter();
		return ch;
	}

	cDirection convertToDirection(char ch) {
		switch (ch) {
			case 'w':
				return cDirection{ cDirection::up };
			case 'a':
				return cDirection{ cDirection::left };
			case 's':
				return cDirection{ cDirection::down };
			case 'd':
				return cDirection{ cDirection::right };
			default:
				cout << "Invalid Direction" << endl;
				return cDirection{ cDirection::down };
		}
	}
}

class cTile {
private:
	int number;
public:
	cTile(int number = 0)
	{
		this->number = number;
	}

	int getNum() const{
		return number;
	}

	bool isEmpty() {
		return number == 0;
	}

	friend ostream& operator <<(ostream&, const cTile&);
};
ostream& operator <<(ostream& os, const cTile& tile) {
	if (tile.number > 9)
		os << "  " << tile.number << "  ";
	else if (tile.number > 0)
		os << "   " << tile.number << "  ";
	else if (tile.number == 0) 
		os << "     ";
	return os;
}

class cBoard {
private:
	cTile board[4][4];
public:
	cBoard() {
		int count = 1;
		for(int i =0;i<4;i++)
			for (int j = 0; j < 4; j++) {
				board[i][j] = count;
				count++;
			}
		board[3][3] = 0;
	}

	static void printEmptyLines(int count)
	{
		for (int i = 0; i < count; ++i)
			std::cout << '\n';
	}

	static bool isValidPoint(Point pt) {
		return ((pt.x >= 0 && pt.x < 4) && (pt.y >= 0 && pt.y < 4));
	}

	Point getEmptyTile() {
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				if (board[i][j].isEmpty())
					return { i,j };
		cout << "EMPTY TILE DOES NOT EXIST" << endl;
		return { -1,-1 };
	}

	void swapTile(Point p1, Point p2) {
		swap(board[p1.x][p1.y], board[p2.x][p2.y]);
	}

	bool moveTile(cDirection dir) {
		Point emptyTile{ getEmptyTile() };
		Point adjPos{ emptyTile.getAdjacentDirection(-dir) };
		if (!isValidPoint(adjPos))
			return 0;
		swapTile(emptyTile, adjPos);
		return 1;
	}

	void randomize() {
		srand(time(NULL));
		for (int i = 0; i < 1000; i++)
			moveTile(cDirection::getRandomDirection());
	}

	bool isWin() {
		cBoard solved{};
		return solved == *this;
	}

	friend ostream& operator <<(ostream&, const cBoard&);
	friend bool operator==(const cBoard& b1, const cBoard& b2) {
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				if (b1.board[i][j].getNum() != b2.board[i][j].getNum())
					return 0;
		return 1;
	}
};
ostream& operator <<(ostream& os, const cBoard& b) {
	// Before drawing always print some empty lines
	// so that only one board appears at a time
	// and it's always shown at the bottom of the window
	// because console window scrolls automatically when there is no
	// enough space.
	cBoard::printEmptyLines(g_consoleLines); 

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			os << b.board[i][j];
		os << "\n";
	}
	return os;
}

int main() {
	char x;
	cBoard board{};
	cout << board;
	cout << "Welcome to the puzzle game" << endl;
	cout << "Press anything to start: " << endl;
	cin >> x;
	cin.ignore();
	cout << "Generating.....\n" << endl;
	board.randomize();
	cout << board;

	//Show instructions
	cout << "w: "<< cDirection::Instruction() << endl;
	cout << "s: "<<cDirection::Instruction() << endl;
	cout << "a: "<<cDirection::Instruction() << endl;
	cout << "d: "<<cDirection::Instruction() << endl;
	cout << "q:" << " Exit the game" << endl;
	cout << "\n\n\n";
	while (!board.isWin()) {
		char ch = UserInput::getCommandFromUser();

		//Non-direction command
		if (ch == 'q') {
			cout << "Idiot!!!!!!!!!!" << endl;
			return 0;
		}

		//Direction command
		cDirection dir{ UserInput::convertToDirection(ch) };
		cout << "Valid: " << dir << endl;
		bool userMoved{ board.moveTile(dir) };
		if (userMoved) {
			moves++;
			cout << board;
			cout << "                                                Moves: " << moves << endl;
		}
	}
	cout << "\n\nYOU HAVE WON!!!!!!!!!!!!!!!!!" << endl;
	return 0;
}