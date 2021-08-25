#ifndef TETROMINO_MANAGER_HPP
#define TETORMINO_MANAGER_HPP

#include <functional>
#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "Tetromino.hpp"

enum class TetrominoType
{
    I = 0,
    J,
    L,
    O,
    S,
    T,
    Z
};

class TetrominoManager
{
public:
    TetrominoManager();
    ~TetrominoManager();

    void Reset();
    void CreateRandTetromino();
    void DrawTetrominos(sf::RenderWindow *l_wind);

    Tetromino* GetCurrentTetromino();

private:
    std::unordered_map<TetrominoType, std::function<Tetromino*>(void)> tetrominoFactory;
    Tetromino *currentTetromino;
    std::vector<Tetromino*> frozenTetrominos;

    void CreateTetromino(TetrominoType l_type);
};

#endif