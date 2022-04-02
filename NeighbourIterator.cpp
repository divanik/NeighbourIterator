#include <chrono>
#include <iostream>
#include <span>
#include <vector>

template<typename T>
class NeighbourIterator {
public:
    NeighbourIterator(int& n, int& m, std::istream& in) : borders_(n + 2, 0), neighbours_(2 * m) {
        in >> n >> m;
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
        *this = NeighbourIterator(n, inits, neighbours);
    }

    NeighbourIterator(int n, const std::vector<int>& inits, const std::vector<T>& neighbours) : borders_(n + 2, 0), neighbours_(neighbours.size()) {
        for (const int x : inits) {
            borders_[x + 2]++;
        }
        for (int i = 3; i < n + 2; ++i) {
            borders_[i] += borders_[i - 1];
        }
        int cur = 0;
        for (int i = 0; i < neighbours.size(); ++i) {
            neighbours_[borders_[inits[i] + 1]] = std::move(neighbours[i]);
            ++borders_[inits[i] + 1];
        }
        borders_.resize(n + 1);
    }  

    std::span<int> operator[](int u) {
        return {neighbours_.begin() + borders_[u], neighbours_.begin() + borders_[u + 1]};
    }

private:
    std::vector<int> borders_;
    std::vector<T> neighbours_;
};

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> ins(m);
    std::vector<int> outs(m);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        ins[i] = u;
        outs[i] = v;
    }
    NeighbourIterator graph(n, ins, outs);
    for (auto& x : graph[0]) {
        std::cout << x << ' ';
    }
    std::cout << '\n';
}