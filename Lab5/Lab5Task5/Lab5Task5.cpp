#include "cdecl_translate.h"

// Интерпретатор для работы с файлами
void interpretFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filePath << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << cdecl_translate(line) << std::endl;
    }

    file.close();
}

// Главная функция
int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file_path>" << std::endl;
        return 1;
    }

    std::string filePath = argv[1];
    interpretFile(filePath);

    return 0;
}
