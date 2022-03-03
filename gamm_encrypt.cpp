//Задание №2.1
//Реализовать алгоритм шифрования данных «Шифрование методом гаммирования»
//По модулю 2.

#include <iostream>
#include<fstream>
#include<string>

/*
Класс-реализация счётчика
с повтором для ключа
*/
class GammaCounter
{
private:

   //ключ
   std::string gamma;
   //итератор для перебора
   int it;
public:

   /*
   Конструктор по умолчанию
   */
   GammaCounter(){}

   /*
   Конструктор, задающий ключ
   */
   GammaCounter(std::string line)
   {
      gamma = line;
      it = 0;
   }

   /*
   Функция, возвращающая текущую цифру ключа
   */
   char getSymbol()
   {
      //если ключ закончился,
      //он повторяется заново
      if (it == gamma.length())
      {
         it = 0;
      }
      return gamma[it++];
   }
};



/*
Класс-реализация 
шифрования методом гаммирования
по модулю 2 (XOR сложение)
*/
class Enctypt
{

private:

   //строка для шифра
   std::string line;
   //ключ-гамма
   std::string gamma;
   bool isEncrypt;


public:

   Enctypt() 
   {
      line = "";
      gamma = "";
      isEncrypt = false;
   }

   /*
   Конструктор, задающий строку и ключ
   */
   Enctypt(std::string line, std::string gamma)
   {
      this->line = line;
      this->gamma = gamma;
   }

   bool wasEncrypted()
   {
      return isEncrypt;
   }

   bool print()
   {
      if (line == "" || gamma == "")
      {
         return false;
      }
      std::cout
         << "* * * * *"
         << std::endl
         << "Line: "
         << line << std::endl
         << "Gamma: "
         << gamma << std::endl
         << "* * * * *"
         << std::endl;
      return true;
   }

   void setData(std::string line, std::string gamma)
   {
      this->line = line;
      this->gamma = gamma;
      this->isEncrypt = false;
   }

   /*
   Функция для шифрования и
   расшифровки
   */
   std::string encrypt()
   {
      int i = 0;
      GammaCounter key = GammaCounter(gamma);

      //посимвольно применяем побитовое сложение
      while (line[i])
      {
         line[i] = line[i] ^ (int)key.getSymbol();
         i++;
      }

      isEncrypt = !isEncrypt;

      return line;
   }
};

/*
Класс-реализация 
программы 
*/
class MainProgram
{
private:

   //название файла для чтения данных
   std::string fileName;

public:

   /*
   Конструктор, принимающий название файла
   */
   MainProgram(std::string fname)
   {
      fileName = fname;
   }
private:

   /*
   Функция, проверяющая корректность строки
   на наличие цифр*/
   std::string validateString()
   {
      int i = 0;
      std::string line;
      std::getline(std::cin, line);

      if (line.length() == 0)
      {
         std::cout
            << "Enter the non-empty"
            << " line without numbers : ";
         return validateString();
      }
      while (line[i])
      {
         if ('0' <= line[i] && line[i] <= '9')
         {
            std::cout
               << "Enter the non-empty"
               << " line without numbers : ";
            return validateString();
         }
         i++;
      }
      return line;
   }

   /*
   Функция, проверяющая корректность числа
   и выводящая его в виде строки
   */
   std::string strValidateNumber()
   {
      int i = 0;
      std::string line;
      std::getline(std::cin, line);

      if (line.length() == 0)
      {
         std::cout << "Enter the number: ";
         return strValidateNumber();
      }
      while (line[i])
      {
         if ('0' > line[i] || line[i] > '9')
         {           
            std::cout << "Enter the number: ";
            return strValidateNumber();
         }
         i++;
      }
      return line;
   }

   /*
   Функция, проверяющая корректность числа
   и выводящая его в виде числа
   */
   int intValidateNumber()
   {
      int i = 0;
      std::string line;
      std::getline(std::cin, line);

      if (line.length() == 0)
      {
         std::cout << "Enter the number: ";
         return intValidateNumber();
      }
      while (line[i])
      {
         if ( line[i] < '0' || line[i] > '9')
         {
            std::cout << "Enter the number: ";
            return intValidateNumber();
         }
         i++;
      }

      return atoi(line.c_str());
   }

public:

//   /*
//   Функция, реализующая программу
//   через файл
//   */
//   void fileProgram()
//   {
//      std::cout
//         << "File program."
//         << std::endl
//         << std::endl;
//
//      std::ifstream file(fileName);
//
//      std::string line, gamma;
//
//      while (!file.eof())
//      {
//         std::getline(file, line);
//         std::getline(file, gamma);
//         std::cout
//            << "Line: " << line
//            << std::endl
//            << "Gamma: " << gamma
//            << std::endl;
//
//         Enctypt value(line, gamma);
//
//         std::cout
//            << "After enctyping: "
//            << value.encrypt()
//            << std::endl;
//         std::cout
//            << "After decrypting: "
//            << value.encrypt()
//            << std::endl
//            << std::endl;
//      }
//
//      file.close();
//   }

   /*
   Функция, реализующая выбор 
   источника данных
   */
   void mainProgram()
   {
      int choice = -1;
      std::string line, gamma;
      Enctypt value;

      system("cls");

      do
      {
         std::cout
            << "Console program."
            << std::endl
            << "1)Print data "
            << std::endl
            << "2)Set data"
            << std::endl
            << "3)Encrypt"
            << std::endl
            << "4)Decrypt"
            << std::endl
            << "0)Close the program ";
         choice = intValidateNumber();
         switch (choice)
         {
         case 1:

            system("cls");
            if (value.print() == false)
            {
               std::cout
                  << "Data is empty!"
                  << std::endl
                  << std::endl;
            }
            break;

         case 2:

            system("cls");

            std::cout
               << "Enter the line: ";
            line = validateString();
            std::cout
               << "Enter the gamma: ";
            gamma = strValidateNumber();
            value.setData(line, gamma);

            system("cls");
            value.print();

            break;

         case 3:

            system("cls");

            if (value.wasEncrypted() == false)
            {
               value.encrypt();
               value.print();
            }
            else
            {
               std::cout
                  << "Line was encrypted!"
                  << std::endl
                  << std::endl;
            }

            break;

         case 4:

            system("cls");

            if (value.wasEncrypted() == true)
            {
               value.encrypt();
               value.print();
            }
            else
            {
               std::cout
                  << "Line was decrypted!"
                  << std::endl
                  << std::endl;
            }

            break;

         default:
            break;

         }
      } while (choice != 0);
   }
};

int main()
{
   MainProgram program("file.txt");

   program.mainProgram();

   return 8;
}