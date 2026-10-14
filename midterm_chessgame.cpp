#include <array>
#include <iostream>
#include <string>

using Board = std::array<std::array<char, 8>, 8>;

void printBoard(const Board& board) {
	std::cout << "\n  a b c d e f g h\n";
	for (int row = 0; row < 8; ++row) {
		std::cout << 8 - row << ' ';
		for (int col = 0; col < 8; ++col) {
			std::cout << board[row][col] << ' ';
		}
		std::cout << 8 - row << '\n';
	}
	std::cout << "  a b c d e f g h\n\n";
}

bool parseSquare(const std::string& square, int& row, int& col) {
	if (square.length() != 2 || square[0] < 'a' || square[0] > 'h' ||
		square[1] < '1' || square[1] > '8') {
		return false;
	}

	col = square[0] - 'a';
	row = 8 - (square[1] - '0');
	return true;
}

bool isLegalPawnMove(const Board& board, int fromRow, int fromCol,
					 int toRow, int toCol, char pawn) {
	const int direction = pawn == 'P' ? -1 : 1;
	const int startingRow = pawn == 'P' ? 6 : 1;
	const char enemyPawn = pawn == 'P' ? 'p' : 'P';
	const int rowChange = toRow - fromRow;
	const int colChange = toCol - fromCol;

	if (colChange == 0 && board[toRow][toCol] == '.') {
		if (rowChange == direction) {
			return true;
		}
		if (fromRow == startingRow && rowChange == 2 * direction &&
			board[fromRow + direction][fromCol] == '.') {
			return true;
		}
	}

	return rowChange == direction && (colChange == 1 || colChange == -1) &&
		   board[toRow][toCol] == enemyPawn;
}

int main() {
	Board board{};
	for (auto& row : board) {
		row.fill('.');
	}
	for (int col = 0; col < 8; ++col) {
		board[1][col] = 'p';
		board[6][col] = 'P';
	}

	char currentPlayer = 'P';
	int moveNumber = 1;
	std::string from, to;

	std::cout << "Pawn-only chess demo (P = White, p = Black)\n";
	std::cout << "Enter moves using squares, for example: e2 e4\n";
	std::cout << "Enter q to quit.\n";
	printBoard(board);

	while (true) {
		std::cout << "Move " << moveNumber << " - "
				  << (currentPlayer == 'P' ? "White" : "Black")
				  << " to move: ";
		if (!(std::cin >> from) || from == "q") {
			break;
		}
		if (!(std::cin >> to)) {
			break;
		}

		int fromRow, fromCol, toRow, toCol;
		if (!parseSquare(from, fromRow, fromCol) ||
			!parseSquare(to, toRow, toCol)) {
			std::cout << "Invalid square. Use a1 through h8.\n";
			continue;
		}
		if (board[fromRow][fromCol] != currentPlayer) {
			std::cout << "That square does not contain your pawn.\n";
			continue;
		}
		if (!isLegalPawnMove(board, fromRow, fromCol, toRow, toCol,
							 currentPlayer)) {
			std::cout << "Illegal pawn move. Try again.\n";
			continue;
		}

		board[toRow][toCol] = currentPlayer;
		board[fromRow][fromCol] = '.';
		std::cout << (currentPlayer == 'P' ? "White" : "Black")
				  << " moved " << from << " to " << to << ".\n";
		printBoard(board);

		if (toRow == 0 || toRow == 7) {
			std::cout << (currentPlayer == 'P' ? "White" : "Black")
					  << " wins by reaching the opposite side!\n";
			break;
		}

		currentPlayer = currentPlayer == 'P' ? 'p' : 'P';
		++moveNumber;
	}

	std::cout << "Game ended.\n";
	return 0;
}
