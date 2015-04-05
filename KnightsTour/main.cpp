#include <iostream>
#include <vector>

/**
 *
 *   0 1 2 3 4
 * 0 # O # O #
 * 1 O # # # O
 * 2 # # R # #
 * 3 O # # # O
 * 4 # O # O #
 */

class Point{
public:
    Point(unsigned int x, unsigned int y) : x(x), y(y) { }

//    Point &operator = (const Point &point) { x = point.x; y = point.y; return *this; }
    bool operator == (const Point &point) { return point.x == x && point.y == y; }

    unsigned int x;
    unsigned int y;
};

static int MovePoints[8][2] = {
    {1, 2},
    {1, -2},
    {-1, 2},
    {-1, -2},

    {2, 1},
    {2, -1},
    {-2, 1},
    {-2, -1}
};

class HorseMove : public Point{
public:
    HorseMove(unsigned int x, unsigned int y) : Point(x, y) { initialized=false; }

    void init() { initialized=true; generateAlloptions(); }

    void generateAlloptions() {
        for(int i = 0; i < 8; ++i) {
            HorseMove horseMove(x+MovePoints[i][0], y+MovePoints[i][1]);

            if((int)x+MovePoints[i][0] > -1 && (int)y+MovePoints[i][1] > -1)
                options.push_back(horseMove);
        }
    }

    HorseMove getNextOption() {
        HorseMove horseNove = options.back();
        options.pop_back();
        return horseNove;
    }

    bool isMoreOptions() { return options.size() != 0; }

    bool initialized;
    std::vector<HorseMove> options;
};

class Board{
public:
    typedef std::vector<int> LineType;
    typedef std::vector<LineType> BoardType;

    BoardType board;

    Board(int x, int y) { initBoard(x, y); }

    void initBoard(int x, int y) {
        board.resize(x);

        for(BoardType::size_type i = 0; i < board.size(); i++)
        {
            board[i].resize(y);
        }
    }

    bool isHorseTryValid(const HorseMove &horseMove) {
        return board.size() > horseMove.x && board.size() > horseMove.y
                && board[horseMove.x][horseMove.y] == 0;
    }

    void registorHorseMove(const HorseMove &horseMove, int number)
    {
        board[horseMove.x][horseMove.y] = number;
    }

    void cancelHorseMove(const HorseMove &horseMove)
    {
         board[horseMove.x][horseMove.y] = 0;
    }

    void printBoard() {
        for(BoardType::size_type i = 0; i < board.size(); ++i)
        {
            for(LineType::size_type j = 0; j < board[i].size(); ++j)
                std::cout << board[i][j] << "   ";
            std::cout << std::endl;
        }
    }

    bool allPointsMarked() {
        for(BoardType::size_type i = 0; i < board.size(); ++i) {
            for(LineType::size_type j = 0; j < board[i].size(); ++j) {
                if(board[i][j] == 0)
                    return false;
            }
        }

        return true;
    }

};

/**
 * @brief The Knight class
 *
 */

class Knight{
public:
    Knight(HorseMove &firstNove, Board &board) : board(board) { firstNove.init(); moveTo(firstNove); }

    void cancelLastMove() { board.cancelHorseMove(lastMoves.back()); lastMoves.pop_back(); }
    void moveTo(const HorseMove &horseMove) {
        if(!board.isHorseTryValid(horseMove)) {
            return;
        }

        lastMoves.push_back(horseMove);
        board.registorHorseMove(horseMove, lastMoves.size());
    }

    void moveToNextPoint() {
        if(lastMoves.size() == 0)
        {
            std::cout << "It's bad but there's no more options, fix your program!" << std::endl;
            return;
        }

        if(!lastMoves.back().initialized) {
            lastMoves.back().init();
        }

        if(!lastMoves.back().isMoreOptions()) {
            cancelLastMove();
            return moveToNextPoint();
        }

        HorseMove horseMove = lastMoves.back().getNextOption();

        if(!board.isHorseTryValid(horseMove))
            return moveToNextPoint(); // The wrong move already poped. (in getNextOption() function)

        moveTo(horseMove);
    }

private:
    std::vector<HorseMove> lastMoves;

    Board &board;
};

int main()
{
    Board board(6, 6);
    HorseMove firstHorseMove(0, 0);
    Knight knight(firstHorseMove, board);

    while(!board.allPointsMarked())
    {
        knight.moveToNextPoint();
    }

    board.printBoard();

    return 0;
}

