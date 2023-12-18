#include <iostream>
#include <vector>

struct TowerState
{
    std::vector<std::vector<int>> towers{};

    TowerState(int numTowers, int numDisks)
    {
        for (int i = 0; i < numTowers; ++i)
        {
            towers.push_back({});
        }

        for (int i = numDisks; i >= 1; --i)
        {
            towers[0].push_back(i);
        }
    }
};

auto moveDisk(int sourceTower, int targetTower, TowerState &state, int &moveCount) -> void
{
    int disk = state.towers[sourceTower].back();
    state.towers[sourceTower].pop_back();
    state.towers[targetTower].push_back(disk);
    moveCount++;
}

auto printState(const TowerState &state) -> void
{
    for (size_t i = 0; i < state.towers.size(); ++i)
    {
        std::cout << "Tower " << i + 1 << ": ";
        for (int disk : state.towers[i])
        {
            std::cout << disk << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "-------------" << std::endl;
}

auto hanoiStewart(int numTowers, int numDisks, TowerState &state, int sourceTower, int targetTower, int auxiliaryTower, int &moveCount) -> void
{
    if (numDisks > 0)
    {
        hanoiStewart(numTowers, numDisks - 1, state, sourceTower, auxiliaryTower, targetTower, moveCount);

        moveDisk(sourceTower, targetTower, state, moveCount);
        printState(state);

        hanoiStewart(numTowers, numDisks - 1, state, auxiliaryTower, targetTower, sourceTower, moveCount);
    }
}

auto main() -> int
{
    int numTowers = 3;
    int numDisks = 8;

    TowerState initialState(numTowers, numDisks);
    std::cout << "The initial state of the towers:" << std::endl;
    printState(initialState);

    int moveCount = 0;
    hanoiStewart(numTowers, numDisks, initialState, 0, numTowers - 1, 1, moveCount);

    std::cout << "Number of moves:d " << moveCount << std::endl;

    return 0;
}
