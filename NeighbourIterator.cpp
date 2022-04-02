#include <iostream>
#include <span>
#include <vector>


class NeighbourIterator {
public:
    NeighbourIterator(int n, int m, std::istream& in) : borders_(n + 2, 0), neighbours_(2 * m) {
        std::vector<int> inits(2 * m);
        std::vector<int> neighbours(2 * m);
        int u, v;
        for (int i = 0; i < m; ++i) {
            in >> u >> v; u--; v--;
            inits[i * 2] = u;
            inits[i * 2 + 1] = v;
            neighbours[i * 2] = v;
            neighbours[i * 2 + 1] = u;
            borders_[u + 2]++;
            borders_[v + 2]++;
        }
        for (int i = 3; i < n + 2; ++i) {
            borders_[i] += borders_[i - 1];
        }
        int cur = 0;
        for (int i = 0; i < 2 * m; ++i) {
            neighbours_[borders_[inits[i] + 1]] = neighbours[i];
            ++borders_[inits[i] + 1];
        }
        borders_.resize(n + 1);
        for (auto& x : borders_) {
            std::cout << x << ' ';
        }
        std::cout << '\n';
        for (auto& x : neighbours_) {
            std::cout << x << ' ';
        }
        std::cout << '\n';
    }  

    std::span<int> operator[](int u) {
        std::cout << u << std::endl;
        return {neighbours_.begin() + borders_[u], neighbours_.begin() + borders_[u + 1]};
    }

private:
    std::vector<int> borders_;
    std::vector<int> neighbours_;
};

int main() {
    int n, m;
    std::cin >> n >> m;
    NeighbourIterator graph(n, m, std::cin);
    for (auto& x : graph[0]) {
        std::cout << x << ' ';
    }
    std::cout << '\n';
}