#include "basics.hpp"



int main() {
    std::ofstream f, f1;
    
    int n = 8;
    std::vector<std::pair<int, int>> m = { std::pair<int, int>(0,6), std::pair<int, int>(1,7), std::pair<int, int>(0,7), std::pair<int, int>(6, 7), std::pair<int, int>(3,5), std::pair<int, int>(4,5) };
    DSU<int> dsu(8);
    std::vector<int> tmp = dsu.RAM_algorithm(m);
    for (int i = 0; i < n; i++)
        std::cout << i+1 <<": " << tmp[i] << std::endl;
    std::cout << std::endl;
    DSU_path_compression<int> dsu1(n);
    std::vector<int> tmp1 = dsu1.RAM_algorithm(m);
    for (int i = 0; i < n; i++)
        std::cout << i + 1 << ": " << tmp1[i] << std::endl;



    f.open("Experiment1.csv");
    f1.open("Experiment1_no_comp.csv");
    f << "1st experiment, path compression is implemented, m = (n^2)/10;\n";
    f1 << "1st experiment, path compression is NOT implemented, m = (n^2)/10;\n";

    for (int i = 1; i <= 1001; i+=10){
        std::cout << i << std::endl;
        DSU<int> dsu(i);
        DSU_path_compression<int> dsu1(i);

        std::vector<std::pair<int, int>> generated = pseudo_random_edges(i, (i*i)/10);

        const auto Tstart{ std::chrono::steady_clock::now() };
        std::vector<int> res = dsu.RAM_algorithm(generated);
        const auto Tend{ std::chrono::steady_clock::now() };
        const std::chrono::duration<double> elapsed_seconds{Tend - Tstart};
        f << i << ";" << elapsed_seconds.count() << ";\n";

        const auto Tstart1{ std::chrono::steady_clock::now() };
        std::vector<int> res1 = dsu1.RAM_algorithm(generated);
        const auto Tend1{ std::chrono::steady_clock::now() };
        const std::chrono::duration<double> elapsed_seconds1{Tend1 - Tstart1};
        f1 <<i << ";" <<elapsed_seconds1.count() <<";\n";
    }
    f.close();
    f1.close();



    f.open("Experiment2.csv");
    f1.open("Experiment2_no_comp.csv");
    f << "2nd experiment, path compression is implemented, m = n-1;\n";
    f1 << "2nd experiment, path compression is NOT implemented, m = n-1;\n";

    for (int i = 1; i <= 1001; i += 10) {
        std::cout << i << std::endl;
        DSU<int> dsu(i);
        DSU_path_compression<int> dsu1(i);

        std::vector<std::pair<int, int>> generated = pseudo_random_edges(i, (i * i) / 10);

        const auto Tstart{ std::chrono::steady_clock::now() };
        std::vector<int> res = dsu.RAM_algorithm(generated);
        const auto Tend{ std::chrono::steady_clock::now() };
        const std::chrono::duration<double> elapsed_seconds{ Tend - Tstart };
        f << i << ";" << elapsed_seconds.count() << ";\n";

        const auto Tstart1{ std::chrono::steady_clock::now() };
        std::vector<int> res1 = dsu1.RAM_algorithm(generated);
        const auto Tend1{ std::chrono::steady_clock::now() };
        const std::chrono::duration<double> elapsed_seconds1{ Tend1 - Tstart1 };
        f1 << i << ";" << elapsed_seconds1.count() << ";\n";
    }
    f.close();
    f1.close();



    f.open("Experiment3.csv");
    f1.open("Experiment3_no_comp.csv");
    f << "3rd experiment, path compression is implemented, m = log(n);\n";
    f1 << "3rd experiment, path compression is NOT implemented, m = log(n);\n";

    for (int i = 1; i <= 1001; i += 10) {
        std::cout << i << std::endl;
        DSU<int> dsu(i);
        DSU_path_compression<int> dsu1(i);

        std::vector<std::pair<int, int>> generated = pseudo_random_edges(i, (int)(std::log((double)i)/std::log(2.0)));

        const auto Tstart{ std::chrono::steady_clock::now() };
        std::vector<int> res = dsu.RAM_algorithm(generated);
        const auto Tend{ std::chrono::steady_clock::now() };
        const std::chrono::duration<double> elapsed_seconds{ Tend - Tstart };
        f << i << ";" << elapsed_seconds.count() << ";\n";

        const auto Tstart1{ std::chrono::steady_clock::now() };
        std::vector<int> res1 = dsu1.RAM_algorithm(generated);
        const auto Tend1{ std::chrono::steady_clock::now() };
        const std::chrono::duration<double> elapsed_seconds1{ Tend1 - Tstart1 };
        f1 << i << ";" << elapsed_seconds1.count() << ";\n";
    }
    f.close();
    f1.close();



    f.open("Experiment4.csv");
    f1.open("Experiment4_no_comp.csv");
    f << "generate untill fully connected, path compression is implemented;\n";
    f1 << "generate untill fully connected, path compression is NOT implemented;\n";

    for (int i = 1; i <= 1001; i += 10) {
        std::cout << i << std::endl;
        DSU<int> dsu(i);
        DSU_path_compression<int> dsu1(i);
        bool flag = true;
        double counter_time = 0;
        while (flag) {
            std::vector<std::pair<int, int>> generated = pseudo_random_edges(i, 5);

            const auto Tstart{ std::chrono::steady_clock::now() };
            std::vector<int> res = dsu.RAM_algorithm(generated);
            const auto Tend{ std::chrono::steady_clock::now() };
            const std::chrono::duration<double> elapsed_seconds{ Tend - Tstart };
            counter_time += elapsed_seconds.count();
            flag = false;
            for (int i = 0; i < res.size(); i++) {
                if (flag)
                    break;
                for (int j = 0; j < i; j++)
                    if (res[i] != res[j]) {
                        flag = true;
                        break;
                    }
            }
        }
        f << i << ";" << counter_time << ";\n";
        counter_time = 0.0;
        flag = true;
        while (flag) {
            std::vector<std::pair<int, int>> generated = pseudo_random_edges(i, 5);
            double counter_time = 0;
            const auto Tstart{ std::chrono::steady_clock::now() };
            std::vector<int> res1 = dsu1.RAM_algorithm(generated);
            const auto Tend{ std::chrono::steady_clock::now() };
            const std::chrono::duration<double> elapsed_seconds{ Tend - Tstart };
            counter_time += elapsed_seconds.count();
            flag = false;
            for (int i = 0; i < res1.size(); i++)
                for (int j = 0; j < i; j++)
                    if (res1[i] != res1[j]) {
                        flag = true;
                        break;
                    }
        }
        f1 << i <<";" << counter_time << ";\n";
    }
    f.close();
    f1.close();
}