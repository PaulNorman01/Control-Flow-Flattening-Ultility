
#include <iostream>
#include <string>
#include <random>
#include <Windows.h>

std::string Fillers();


int getRandomNumber() {
    HCRYPTPROV hCryptProv;
    DWORD dwBytesToGenerate = 1;
    BYTE pbBuffer[sizeof(DWORD)];
    if (!CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
        return 0; // error acquiring context
    }
    if (!CryptGenRandom(hCryptProv, dwBytesToGenerate, pbBuffer)) {
        CryptReleaseContext(hCryptProv, 0);
        return 0; // error generating random number
    }
    CryptReleaseContext(hCryptProv, 0);
    DWORD randomNumber;
    memcpy(&randomNumber, pbBuffer, sizeof(DWORD));

    std::random_device rd5;
    std::mt19937 gen5(rd5());

    std::uniform_int_distribution<> nested_dist5(0, 140);
    std::uniform_int_distribution<> nested_dist6(120, 177);

    unsigned int ReturnNumber;

    if ((unsigned int)nested_dist6(gen5) > 160)
    {
         ReturnNumber = (unsigned int)randomNumber + (unsigned int)nested_dist6(gen5);
    }

    else if((unsigned int)nested_dist6(gen5) < 140)
    {
        std::random_device rd6;
        std::mt19937 gen6(rd6());
        std::uniform_int_distribution<> nested_dist10(1000, 1400);

         ReturnNumber = (unsigned int)randomNumber % (unsigned int)nested_dist10(gen6);
    }

    else
    {
        std::random_device rd6;
        std::mt19937 gen6(rd6());
        std::uniform_int_distribution<> nested_dist10(10000, 14000);

        ReturnNumber = (unsigned int)randomNumber % (unsigned int)nested_dist10(gen6);
    }

    return ReturnNumber;
}

std::string random_string()
{
    std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

    std::random_device rd;
    std::mt19937 generator(rd());

    std::shuffle(str.begin(), str.end(), generator);

    return str.substr(0, 32);    // assumes 32 < number of characters in str         
}

std::string nested_variables(int NestedCallerLoopNum)
{
    unsigned int nested_num = ((unsigned int)getRandomNumber()) % 7 + 1;
    unsigned int TypeCond = ((unsigned int)getRandomNumber()) % 2;
    unsigned int OperationDice;

    std::string type = "    ";
    std::string var = "     ";
    std::string ReturnNested = "    ";
    std::string VariableNumber = "   ";


    //j < nested_num
    //for (int j = 0; j < 1; ++j)
    for (int j = 0; j < nested_num; ++j)
    {
        OperationDice = (unsigned int)getRandomNumber() % 4;

        VariableNumber = std::to_string((unsigned int)getRandomNumber());

        type = (TypeCond == 1) ? "unsigned int" : "int";
        var = type + " y" + VariableNumber + " = " + std::to_string((unsigned int)getRandomNumber() % 200) + ";\n";
        var += " y" + VariableNumber + " ^= " + std::to_string(getRandomNumber()) + ";\n";

        switch (OperationDice)
        //switch (3)
        {
        case 0:
        {
            std::string CharVarNumber = std::to_string((unsigned int)getRandomNumber());
            var += " char CH" + CharVarNumber + " = \'";

            for (int CharacterIterator = 0; CharacterIterator < 4; CharacterIterator++)
                var += "\\x" + std::to_string((unsigned int)getRandomNumber() % 60 + 10);

            var += "\';\n char* OWK" + std::to_string((unsigned int)getRandomNumber()) + " = &CH" + CharVarNumber + ";\n";
            var += "sizeof(CH" + CharVarNumber + ") / sizeof(&CH" + CharVarNumber + ");\n";

            break;
        }

        case 1:
        {
            var += " y" + VariableNumber + "--;\n";
            var += " y" + VariableNumber + " >>= " + std::to_string((unsigned int)getRandomNumber() % 1000) + ";\n";

            break;
        }

        case 2:
        {
            var += " y" + VariableNumber + " += " + std::to_string((unsigned int)getRandomNumber() % 100) + ";\n";
            var += " y" + VariableNumber + " <<= " + std::to_string((unsigned int)getRandomNumber() % 1000) + ";\n";
            std::string adw = "\x11";
            break;
        }

        //will be moved to fillers
        case 3:
        {
            std::string ClassNumber = std::to_string((unsigned int)getRandomNumber());
            std::string Dicer = std::to_string((unsigned int)getRandomNumber());

            var += "class KHG" + ClassNumber + " { \n  public:\n   double DXA" + Dicer + " = " + std::to_string((unsigned int)getRandomNumber() % 100) + "." + std::to_string((unsigned int)getRandomNumber() % 100) + ";\n";
            var += "  void OUW" + Dicer + "(double AYW" + Dicer + "){\n static_cast <double> (AYW" + Dicer + ") + 5." + std::to_string((unsigned int)getRandomNumber() % 1000) + ";";
            var += "sizeof(AYW" + Dicer + ")/sizeof(DXA" + Dicer + ");";

            //ClassIterator < (unsigned int)getRandomNumber() % 5
            for (int ClassIterator = 0; ClassIterator < 1; ClassIterator++)
            {
                std::string NestedClassNumber = std::to_string((unsigned int)getRandomNumber());
                std::string NestedDicer = std::to_string((unsigned int)getRandomNumber());

                var += "\n class KHG" + NestedClassNumber + " { \n  public:\n   double DXA" + NestedDicer + " = " + std::to_string((unsigned int)getRandomNumber() % 100) + "." + std::to_string((unsigned int)getRandomNumber() % 100) + ";\n";
                var += "  void POS" + NestedDicer + "() { \n int aa = 2;";
                
                if (NestedCallerLoopNum > 0)
                {
                    NestedCallerLoopNum--;
                    var += nested_variables(NestedCallerLoopNum);
                }

                var += "\n}\n } NestedObject" + NestedDicer + ";\n\n";

                var += Fillers() + "\n";
                var += "  NestedObject" + NestedDicer + ".POS" + NestedDicer + "();\n";
                var += "\n}\n} SomeObject" + Dicer + "; \n";


                var += "  SomeObject" + Dicer + "." + "OUW" + Dicer + "(" + std::to_string((unsigned int)getRandomNumber()) + ");\n";
            }

            break;
        }
        }

        ReturnNested += "    " + var + "\n";
    }

    return ReturnNested;
}



std::string Fillers()
{
    std::random_device rd3;
    std::mt19937 gen3(rd3());
    std::uniform_int_distribution<> nested_dist3(0, 5);
    std::uniform_int_distribution<> RandomChar(0, 99);

    switch (nested_dist3(gen3))
    {
    case 0:
    {
        //b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
        unsigned int VariableNumber = getRandomNumber();
        std::string FillerString = "\n      ";
        FillerString += "unsigned char b" + std::to_string(VariableNumber) + " = 0x" + std::to_string(RandomChar(gen3)) + ";\n";
        std::string bitNumber = std::to_string((unsigned int)getRandomNumber() % 10);
        FillerString += "      b" + std::to_string(VariableNumber) + " = (b" + std::to_string(VariableNumber) + "\& 0x" + std::to_string((unsigned int)getRandomNumber() % 100) + ") >> " + bitNumber + " | (b" + std::to_string(VariableNumber) + " & 0x" + std::to_string((unsigned int)getRandomNumber() % 100) + ") << " + bitNumber + ";\n";

        return FillerString;

        break;
    }

    case 1:
    {
        std::string FillerString = "\n      ";
        FillerString += "int arr[] = {";
        unsigned int ArraySize = (unsigned int)getRandomNumber() % 20 + 1;

        for (int iterator = 0; iterator < ArraySize; iterator++)
        {

            FillerString += std::to_string((unsigned int)getRandomNumber() % 10);
            if (iterator < ArraySize - 1)
                FillerString += ",";
        }

        FillerString += "}; int n = sizeof(arr)/sizeof(arr[0]); for (int i = 0; i < n-1; i++) for (int j = 0; j < n-i-1; j++) if (arr[j] > arr[j+1]) { int temp = arr[j]; arr[j] = arr[j+1]; arr[j+1] = temp; } for (int i = 0; i < n; i++) arr[i] = i ^ arr[i]; ";

        return FillerString;

        break;
    }
    case 2:
    {
        std::string VarNumber = std::to_string((unsigned int)getRandomNumber());
        std::string FillerString = "\n      ";
        FillerString += "std::vector<int> instructions" + VarNumber + " = {";

        unsigned int ArraySize = (unsigned int)getRandomNumber() % 20;
        for (int iterator = 0; iterator < ArraySize; iterator++)
        {
            FillerString += std::to_string((unsigned int)getRandomNumber() % 10);
            if (iterator < ArraySize - 1)
                FillerString += ",";
        }

        std::string variableNumber = std::to_string((unsigned int)getRandomNumber());

        FillerString += "};  std::random_device rd" + variableNumber + "; std::mt19937 g" + variableNumber + "(rd" + variableNumber + "()); std::shuffle(instructions"+ VarNumber +".begin(), instructions" + VarNumber + ".end(), g" + variableNumber + "); for (int instruction" + VarNumber + " : instructions" + VarNumber + ") {auto add = [](int x, int y) { return x + y; };}";
        return FillerString;

        break;
    }

    case 3:
    {
        std::string FillerString = "\n      ";
        FillerString += "const char* str = \"" + random_string() + "\"; int len = strlen(str); bool is_palindrome = true; for (int i = 0; i < len / 2; i++) if (*(str + i) != *(str + len - i - 1)) { is_palindrome = false; break; }     printf(is_palindrome ? \"\" : \"\"); ";
        return FillerString;

        break;
    }


    case 4:
    {
        std::string MatrixSize = std::to_string(((unsigned int) getRandomNumber() % 10) + 3);
        std::string VarNumber = std::to_string((unsigned int) getRandomNumber());

        std::string FillerString = "\n      ";

        std::string FirstVar = "int G" + VarNumber + "[" + MatrixSize + "]" + "[" + MatrixSize + "]; ";
        std::string SecondVar = "int K" + VarNumber + "[" + MatrixSize + "]" + "[" + MatrixSize + "]; ";
        std::string ThirdVar = "int O" + VarNumber + "[" + MatrixSize + "]" + "[" + MatrixSize + "]; ";

        FillerString += FirstVar + SecondVar + ThirdVar + "for (int iter" + VarNumber + " = 0; iter" + VarNumber + " < " + MatrixSize + "; iter" + VarNumber + "++) { for (int Iterator" + VarNumber + " = 0; Iterator" + VarNumber + " < " + MatrixSize + "; Iterator" + VarNumber + "++) {";
        FillerString += "O" + VarNumber + "[iter" + VarNumber + "][Iterator" + VarNumber + "] = 0; for (int Iteral" + VarNumber + " = 0; Iteral" + VarNumber + " < " + MatrixSize + "; Iteral" + VarNumber + "++) { ";
        FillerString += "O" + VarNumber + "[iter" + VarNumber + "][Iterator" + VarNumber + "] += G" + VarNumber + "[iter" + VarNumber + "][Iteral" + VarNumber + "] * K" + VarNumber + "[Iteral" + VarNumber + "][Iterator" + VarNumber + "]; }}}";
        
        return FillerString;

        break;
    }

    case 5:
    {
        std::string VarNumber = std::to_string((unsigned int)getRandomNumber());
        std::string FillerString = "\n      float LAPW" + VarNumber + " = " + std::to_string(((unsigned int)getRandomNumber() % 10)) + ";";
        FillerString += "\n      while(LAPW" + VarNumber + " > " + std::to_string(((unsigned int)getRandomNumber() % 100) + 12) + "){";
        FillerString += "\n      exit(0);}";

        return FillerString;

        break;
    }
    }
}

std::string NestedCase(int n, int ClassLooper)
{

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> nested_dist(0, 1);
    std::uniform_int_distribution<> num_cases(2, 4);
    std::uniform_int_distribution<> val_dist(0, 999);
    std::uniform_int_distribution<> type_dist(0, 1);
    std::uniform_int_distribution<> loop_dist(0, 3);
    std::uniform_int_distribution<> iter_dist(2, 10);
    std::uniform_int_distribution<> NestNums(1, 3);

    std::string code = "switch(0) {\n";

    int nested_num = num_cases(gen);

    std::string nested_vars;
    std::string var = "     ";


    for (int j = 0; j < nested_num; ++j)
    {
        nested_vars += "    " + nested_variables(ClassLooper); + "\n";

        code += "      case " + std::to_string(j) + ":\n{\n";
        code += nested_vars;
        code += Fillers();

        // Check if a loop should be added
        if (loop_dist(gen) > 0)
        {

            std::string loop_type = (loop_dist(gen) == 1) ? "for" : "while";
            int loop_iter = iter_dist(gen);

            std::string loop_code = "    ";
            if (loop_type == "while")
            {
                unsigned int IteratorNumber = getRandomNumber();
                loop_code = "\n     unsigned int Iterator" + std::to_string(IteratorNumber) + " = " + std::to_string(IteratorNumber + 2) + ";\n";
                loop_code += "    " + loop_type + " (Iterator" + std::to_string(IteratorNumber) + " < " + std::to_string(IteratorNumber + 10) + ") {\n    Iterator" + std::to_string(IteratorNumber) + "++;\n";
                loop_code += "      std::cout << \"WHILE  LOOP \" <<  std::endl;\n";

            }

            if (loop_type == "for")
            {
                std::string iter_name = "i";
                loop_code = "    " + loop_type + " (int " + iter_name + " = 0; " + iter_name + " < " + std::to_string(loop_iter) + "; ++" + iter_name + ") {\n";
                
                std::string VarNumber = std::to_string((unsigned int)getRandomNumber());
                std::string FillerString = "\n      float LAPW" + VarNumber + " = " + std::to_string(((unsigned int)getRandomNumber() % 10)) + ";";
                FillerString += "\n      while(LAPW" + VarNumber + " > " + std::to_string(((unsigned int)getRandomNumber() % 100) + 12) + "){";
                FillerString += "\n      return 0;}";
                loop_code += FillerString;
            }

            loop_code += Fillers();

            if (n > 0)
            {
                n--;
                loop_code += NestedCase(n, ClassLooper);
            }

            loop_code += nested_vars;
            loop_code += "    }\n";
            code += loop_code;
        }
        code += "        }\n";
    }

    code += "    }\n";
    return code;

}



int main()
{
    std::random_device rd2;
    std::mt19937 gen2(rd2());
    std::uniform_int_distribution<> nested_dist2(2, 4);
    std::uniform_int_distribution<> ClassLooper(2, 8);


    //std::cout << (unsigned int)getRandomNumber() % 10 << std::endl;
    //std::cout << Fillers();
    std::cout << NestedCase(nested_dist2(gen2), ClassLooper(gen2));
    //std::cout << nested_variables(ClassLooper(gen2));

}
