#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>


std::string extractName( const std::string &line ) {

    std::cout << "IN EXTRACNT\n";
	std::istringstream ss( line );
	std::string token;
	std::string name;

	while ( ss >> token ) {

		if ( std::all_of( token.begin(), token.end(), ::isdigit ) ) {

			continue;

		}
		else {

			name += token + "";

		}

	}

	if ( !name.empty() ) {

		name.pop_back();

	}

    

	return name;
}

void replaceLines( const std::string &file1, const std::string &file2 ) {
    setlocale( LC_ALL, "" );
    std::cout << "in Replace\n";
    std::ifstream inFile1( file1 );
    std::ifstream inFile2( file2 );

    if ( !inFile1.is_open() || !inFile2.is_open() ) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    std::vector<std::string> lines1;
    std::vector<std::string> lines2;
    std::string line;

    // Чтение строк из первого файла
    while ( std::getline( inFile1, line ) ) {
        lines1.push_back( line );
    }
    inFile1.close();

    // Чтение строк из второго файла
    while ( std::getline( inFile2, line ) ) {
        lines2.push_back( line );
    }
    inFile2.close();
    std::cout << "here1\n";
     //Проход по строкам первого файла
    /*std::cout << lines2.size() << std::endl;
    for ( int i = 0; i < lines2.size(); i++ ) {
    
        std::cout << lines2[ i ] << std::endl;
    
    }*/
    for ( size_t i = 0; i < lines1.size(); ++i ) {
        std::cout << "Processing line " << i << std::endl;
        std::string name1 = extractName( lines1[ i ] );
        bool foundMatch = false;  // Флаг для отслеживания наличия соответствия

        for ( size_t j = 0; j < lines2.size(); ++j ) {
            std::cout << "  Comparing with line " << j << std::endl;
            std::string name2 = extractName( lines2[ j ] );

            if ( name1 == name2 ) {
                lines1[ i ] = lines2[ j ];
                foundMatch = true;  // Устанавливаем флаг, что соответствие найдено
                break;  // Прерываем цикл после первого соответствия
            }
        }

        if ( !foundMatch ) {
            // Дополнительные действия, если соответствие не найдено
            std::cout << "No match found for line " << i << std::endl;
        }

        std::cout << "Finished processing line " << i << std::endl;
    }

    // Запись обновленных строк в первый файл
    std::ofstream outFile( file1 );
    for ( const auto &updatedLine : lines1 ) {
        outFile << updatedLine << std::endl;
    }
    outFile.close();
    std::cout << "end\n";
}


int main()
{
	std::string file1 = "file1.txt";
	std::string file2 = "file2.txt";
	replaceLines( file1, file2 );
	//std::cout << "Hello World!\n";
}
