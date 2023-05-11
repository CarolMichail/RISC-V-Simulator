#include <iostream>
#include<fstream>
#include<map>
#include<vector>
#include<string>
#include<sstream>
#include<bitset>
using namespace std;

//Virtual Mmeory
map <int, int> memory;
map<string, unsigned int> AddressLabel;
map<int,string>InstructionMem;
map<int, int> registers;
map<int, string> labels;

// PC
int PC = 0x100;
int reg_num = 31;
int address=0x100;
string decimalToBinary(int num)
{
    string binary;
    for (int i = 31; i >= 0; i--)
    {
        int bit = (num >> i) & 1;
        binary += to_string(bit);
    }
    return binary;
}
int binaryToDecimal(string binary)
{
    int decimal = 0;
    int position = 1;
    for (int i = binary.size() - 1; i >= 0; i--)
    {
        if (binary[i] == '1')
        {
            decimal += position;
        }
        position *= 2;
    }
    return decimal;
}
//Instructions
int bne(string labelName, const vector<string> operands);
int beq(string labelName, const vector<string> operands);
int bge(string labelName, const vector<string> operands);
int blt(string labelName, const vector<string> operands);
int bltu(string labelName, const vector<string> operands);
int bgeu(string labelName, const vector<string> operands);
void add(const vector<string> operands);
void addi(const vector<string> operands);
void sub(const vector<string> operands);
void and_func(const vector<string> operands);
void andi(const vector<string> operands);
void ori(const vector<string> operands);
void or_func(const vector<string> operands);
void xor_func(const vector<string> operands);
void xori(const vector<string> operands);
void srai(const vector<string> operands);
void slli(const vector<string> operands);
void sll(const vector<string> operands);
void srl(const vector<string> operands);
void sltui(const vector<string> operands);
void srl(const vector<string> operands);
void sltui(const vector<string> operands);
void sltu(const vector<string> operands);
void srli(const vector<string> operands);
void sra(const vector<string> operands);
void lb(string address);
void lbu(string address);
void lw(string line);
void lh(string offset);
void lhu(string offset);
void sw(uint32_t data, int offset);
void sh(uint16_t data, int offset);
void auipc(const vector<string> operands);
void sb(uint8_t value, uint32_t address);
void lui(int reg_num, int immediate);
int jalr( const vector<string> operands, int PC);
int jal(string labelName, const vector<string> operands);


map<int, int> initialize_registers() {
    ifstream file("/Users/muhammadabdelmohsen/Desktop/ProjectAssembly/registers.txt");
    string line;

    while (getline(file, line)) {
        istringstream iss(line);
        string reg_name, pseudo_name;
        iss >> reg_name >> pseudo_name;

        if (reg_name == "") continue;

        registers[reg_num] = 0;
        --reg_num;
    }

    return registers;
}
void PrintingANDupdatingRegs(){
    // Print out the register values
   
    for (int i = 0; i < registers.size(); i++) {
        int reg_num = i;
        int value = registers[reg_num];
        cout << "x"<< reg_num << " = " << value << endl;
    }
   
      for (int i = 0; i < registers.size(); i++) {
        int reg_num = i;
        int value = registers[reg_num];
       
    }
 
} ifstream files("/Users/muhammadabdelmohsen/Desktop/ProjectAssembly/data.txt");

    void ReadAndExecute() {
      
        vector<pair<string, int>> instructions; // pair of instruction and address

        ifstream file("/Users/muhammadabdelmohsen/Desktop/ProjectAssembly/instructions.txt");
         string lines;
         int addresss;
         int vall;
         while (getline(files, lines)) {
             // Parse operands from instruction
             string ad = lines.substr(0,lines.find(','));
             addresss=stoi(ad);
             addresss=addresss/4;
             string  val =lines.substr(lines.find(',')+1);
             vall=stoi(val);
             memory[addresss]= vall;
         }
        cout<<"Memory:\n";
         for(int i=0;i<50;i++)
         {cout<<memory[i]<<endl;}
        string Line;
        int Counterr=1;
        vector<string> operands;
        // Read instructions and store them in the instructions vector
        while (!file.eof()) {
            // Parse operands from instruction
            getline(file, Line);
            istringstream iss(Line);
            instructions.push_back(make_pair(Line, PC));
            PC+=4;
        }
        PC=0x100;

        for(int i=0;i<instructions.size();i++){
            istringstream iss(instructions[i].first);
            string l=iss.str();
            if (l.back()== ':') {
            l.pop_back();
            labels.insert(make_pair(instructions[i].second,l));
                    
            }
           
        }
     auto entry=instructions.begin();
     bool branch=false;
     while( entry!=instructions.end()) {
        if (entry->second == PC) {
     
         istringstream iss(entry->first);
           do {
         string operand;
         iss>>operand;
        operands.push_back(operand);
     
      
        } while (iss);

         }
          for (int j=0;j<operands.size();j++)
            {cout<<operands[j]<<" ";}

            if (operands[0] == "lw") {
                lw(Line);
               PC += 4;
        } else if (operands[0] == "lh") {
            lh(Line);
           
            PC += 4;
        } else if (operands[0] == "lhu") {
            lhu(Line);
            PC += 4;
        } else if (operands[0] == "lbu") {
            lbu(Line);
            PC += 4;
        } else if (operands[0] == "sh") {
            int address = stoi(operands[2]);
            int reg_num = stoi(operands[1].substr(1));
            if(reg_num==0){
                return;
            }
            else{
            int value = registers[reg_num];
            sh(static_cast<uint16_t>(value), address);
            PC += 4;}
        }else if (operands[0] == "sw") {
            int address = stoi(operands[2]);
            int reg_num = stoi(operands[1].substr(1));
            if(reg_num==0){
                return;
            }
            else{
            int value = registers[reg_num];
            sw(value, address);
            PC += 4;}
        } // Check for load immediate (li) instruction and execute it
        else if (operands[0] == "lb") {
        int offset = stoi(operands[2]);
        int reg_num = stoi(operands[1].substr(1));
        lb(Line);
        PC += 4;
        } else if (operands[0] == "sb") {
        int address = stoi(operands[2]);
        int reg_num = stoi(operands[1].substr(1));
        int8_t value = registers[reg_num] & 0xff;
        sb(value, address);
        PC += 4;
        }  else if (operands[0] == "auipc") {
            auipc(operands);
            PC += 4;
            registers[0]=0;
        }
        else if (operands[0] == "addi") {
            addi(operands);
            PC += 4;
            registers[0]=0;
        } else if (operands[0] == "add") {
            add(operands);
            PC += 4;
            registers[0]=0;
        } else if (operands[0] == "sub") {
            sub(operands);
            PC += 4;
            registers[0]=0;
        } else if (operands[0] == "or") {
            or_func(operands);
            PC += 4;
            registers[0]=0;
        } else if (operands[0] == "xor") {
            xor_func(operands);
            PC += 4;
            registers[0]=0;
        } else if (operands[0] == "and") {
            and_func(operands);
            PC += 4;
            registers[0]=0;
        } else if (operands[0] == "slli") {
            slli(operands);
            PC += 4;
            registers[0]=0;

        } else if (operands[0] == "srai") {
            srai(operands);
            PC += 4;
            registers[0]=0;
        } else if (operands[0] == "sra") {
            sra(operands);
            PC += 4;
            registers[0]=0;
        } else if (operands[0] == "srl") {
            srl(operands);
            PC += 4;
            registers[0]=0;
        } else if (operands[0] == "sll") {
            sll(operands);
            PC += 4;
            registers[0]=0;
        } else if (operands[0] == "sltu") {
            sltu(operands);
            PC += 4;
            registers[0]=0;
        } else if (operands[0] == "xori") {
            xori(operands);
            PC +=4;
            registers[0]=0;
        } else if (operands[0] == "ori") {
            ori(operands);
            PC += 4;
            registers[0]=0;
        } else if (operands[0] == "sltui") {
            sltui(operands);
            PC += 4;
            registers[0]=0;
        } else if (operands[0] == "srli") {
            srli(operands);
            PC += 4;
            registers[0]=0;

        } else if (operands[0].back() == ':') {
            PC += 4;
        } else if (operands[0] == "lui") {
            int reg_num = stoi(operands[1].substr(1));
            int immediate = stoi(operands[2]);
            lui(reg_num, immediate);
            PC += 4;
            registers[0]=0;
        } else if (operands[0]=="EBREAK"){
            for (const auto& instruction : instructions) {
                cout << "Line: " << instruction.first << ", PC: " << instruction.second << '\n';
            }
          
            cout<<"The program Counter= "<<PC<<"\n";
            cout<<"**** Program Terminated With EBREAK ****\n";
            return;
        }
        else if(operands[0]=="jalr"){
           PC= jalr(operands,PC);

        }
        else if (operands[0]=="jal"){
            auto itt=instructions.begin();
            int nt=0;
            nt= jal(operands[2],operands);
            PC=nt+4;
        while(itt!=instructions.end())
        {
            if(itt->second==nt){
               branch=true;
               entry=itt;
               cout<<entry->second<<" hena gowa al loop\n";
               break;
            }
            itt++;
        }
         
    }    else if (operands[0]=="bne"){
        auto itt=instructions.begin();
        int nt=0;
        nt= bne(operands[2],operands);
        PC=nt+4;
        while(itt!=instructions.end())
        {
            if(itt->second==nt){
               branch=true;
               entry=itt;
               cout<<entry->second<<" hena gowa al loop\n";
               break;
            }
            itt++;
        }
        }
    else if (operands[0]=="beq"){
    auto itt=instructions.begin();
    int nt=0;
    nt= beq(operands[2],operands);
    PC=nt+4;
    while(itt!=instructions.end())
    {
        if(itt->second==nt){
           branch=true;
           entry=itt;
           cout<<entry->second<<" hena gowa al loop\n";
           break;
        }
        itt++;
    }
     
    } else if (operands[0]=="blt"){
        auto itt=instructions.begin();
        int nt=0;
        nt= blt(operands[2],operands);
        PC=nt+4;
        while(itt!=instructions.end())
        {
            if(itt->second==nt){
               branch=true;
               entry=itt;
               cout<<entry->second<<" hena gowa al loop\n";
               break;
            }
            itt++;
        }
        }
    else if (operands[0]=="bge"){
    auto itt=instructions.begin();
    int nt=0;
    nt= bge(operands[2],operands);
    PC=nt+4;
    while(itt!=instructions.end())
    {
        if(itt->second==nt){
           branch=true;
           entry=itt;
           cout<<entry->second<<" hena gowa al loop\n";
           break;
        }
        itt++;
    }
     
    } else if (operands[0]=="bgtu"){
        auto itt=instructions.begin();
        int nt=0;
        nt= bgeu(operands[2],operands);
        PC=nt+4;
        while(itt!=instructions.end())
        {
            if(itt->second==nt){
               branch=true;
               entry=itt;
               cout<<entry->second<<" hena gowa al loop\n";
               break;
            }
            itt++;
        }
         
        }else if (operands[0]=="bltu"){
            auto itt=instructions.begin();
            int nt=0;
            nt= bltu(operands[2],operands);
            PC=nt+4;
            while(itt!=instructions.end())
            {
                if(itt->second==nt){
                   branch=true;
                   entry=itt;
                   cout<<entry->second<<" hena gowa al loop\n";
                   break;
                }
                itt++;
            }
             
            }
         entry++;
         cout<<"\n";
            cout<<"The registers after "<<Counterr<<" Instructions "<<"\n";
            cout<<"With Program Counter " <<PC<<" of the next instruction:\n";
          
      PrintingANDupdatingRegs();
            
        Counterr++;
        operands.clear();
        }
     
         for (const auto& instruction : instructions) {
             cout << "Line: " << instruction.first << ", PC: " << instruction.second << '\n';
        }
         
}
int main(){
    
    map<string, int> labels;
    map<int, int> registers = initialize_registers();
    ReadAndExecute();
}
int jal(string labelName, const vector<string> operands) {
    // Get the address of the label from the map
   map <int ,string> :: iterator iter;
   for (iter = labels.begin(); iter != labels.end(); iter++)
            {
                 if(operands[2]==(*iter).second){
                    int rd = stoi(operands[1].substr(1));
                    registers[rd] = PC + 4;
                    return (*iter).first;
                }
            }
    return 1;
}
int beq(string labelName, const vector<string> operands) {
    int rs1 = stoi(operands[1].substr(1));
    int rs2 = stoi(operands[2].substr(1));
    labelName=operands[3];

    if (registers[rs1] == registers[rs2]) {
        // Get the address of the label from the map
        map <int ,string> :: iterator iter;
        for (iter = labels.begin(); iter != labels.end(); iter++) {
            if(labelName == (*iter).second){
                return (*iter).first;
            }
        }
    } else  if (registers[rs1] != registers[rs2]){
        bne(labelName, operands);
    }
    
    return PC;
}

int bne(string labelName, const vector<string> operands) {
    int rs1 = stoi(operands[1].substr(1));
    int rs2 = stoi(operands[2].substr(1));
    labelName=operands[3];

    if (registers[rs1] != registers[rs2]) {
        // Get the address of the label from the map
        map <int ,string> :: iterator iter;
        for (iter = labels.begin(); iter != labels.end(); iter++) {
            if(labelName == (*iter).second){
                return (*iter).first;
            }
        }
    }
    
    return PC;
}
int bge(string labelName, const vector<string> operands) {
    int rs1 = stoi(operands[1].substr(1));
    int rs2 = stoi(operands[2].substr(1));
    labelName=operands[3];

    if (registers[rs1] >= registers[rs2]) {
        // Get the address of the label from the map
        map <int ,string> :: iterator iter;
        for (iter = labels.begin(); iter != labels.end(); iter++) {
            if(labelName == (*iter).second){
                return (*iter).first;
            }
        }
    }
    
    return PC;
}
int blt(string labelName, const vector<string> operands) {
    int rs1 = stoi(operands[1].substr(1));
    int rs2 = stoi(operands[2].substr(1));
    labelName=operands[3];

    if (registers[rs1] <= registers[rs2]) {
        // Get the address of the label from the map
        map <int ,string> :: iterator iter;
        for (iter = labels.begin(); iter != labels.end(); iter++) {
            if(labelName == (*iter).second){
                return (*iter).first;
            }
        }
    }
    return PC;
}
int bgeu(string labelName, const vector<string> operands) {
    int rs1 = stoi(operands[1].substr(1));
    int rs2 = stoi(operands[2].substr(1));
    labelName = operands[3];
    if (static_cast<unsigned int>(registers[rs1]) >= static_cast<unsigned int>(registers[rs2])) {
        // Get the address of the label from the map
        map<int, string>::iterator iter;
        for (iter = labels.begin(); iter != labels.end(); iter++) {
            if (labelName == (*iter).second) {
                return (*iter).first;
            }
        }
    }
    return PC;
}
int bltu(string labelName, const vector<string> operands) {
    int rs1 = stoi(operands[1].substr(1));
    int rs2 = stoi(operands[2].substr(1));
    labelName = operands[3];

    if (static_cast<unsigned int>(registers[rs1]) < static_cast<unsigned int>(registers[rs2])) {
        // Get the address of the label from the map
        map<int, string>::iterator iter;
        for (iter = labels.begin(); iter != labels.end(); iter++) {
            if (labelName == (*iter).second) {
                return (*iter).first;
            }
        }
    }
    return PC;
}
void addi(const vector<string> operands) {
    int rd = stoi(operands[1].substr(1));
    int rs1 = stoi(operands[2].substr(1));
    int imm = stoi(operands[3]);

    registers[rd] = registers[rs1] + imm;
}
void add(const vector<string> operands) {
    int rd = stoi(operands[1].substr(1));
    int rs1 = stoi(operands[2].substr(1));
    int rs2 = stoi(operands[3].substr(1));

    registers[rd] = registers[rs1] + registers[rs2];
}
void sub(const vector<string> operands) {
    int rd = stoi(operands[1].substr(1));
    int rs1 = stoi(operands[2].substr(1));
    int rs2 = stoi(operands[3].substr(1));

    registers[rd] = registers[rs1] - registers[rs2];
}
void srai(const vector<string> operands) {
    int rd = stoi(operands[1].substr(1));
    int rs1 = stoi(operands[2].substr(1));
    int imm = stoi(operands[3]);

    registers[rd] = ((int32_t)registers[rs1]) >> imm;
}
void slli(const vector<string> operands) {
    int rd = stoi(operands[1].substr(1));
    int rs1 = stoi(operands[2].substr(1));
    int shamt = stoi(operands[3]);

    registers[rd] = registers[rs1] << shamt;
}
void and_func(const vector<string> operands) {
    int rd = stoi(operands[1].substr(1));
    int rs1 = stoi(operands[2].substr(1));
    int rs2 = stoi(operands[3].substr(1));

    bitset<32> rs1_val(registers[rs1]);
    bitset<32> rs2_val(registers[rs2]);
    bitset<32> result = rs1_val & rs2_val;
    registers[rd] = result.to_ulong();
}
void or_func(const vector<string> operands) {
    int rd = stoi(operands[1].substr(1));
    int rs1 = stoi(operands[2].substr(1));
    int rs2 = stoi(operands[3].substr(1));

    bitset<32> rs1_val(registers[rs1]);
    bitset<32> rs2_val(registers[rs2]);
    bitset<32> result = rs1_val | rs2_val;
    registers[rd] = result.to_ulong();
}
void xor_func(const vector<string> operands) {
    int rd = stoi(operands[1].substr(1));
    int rs1 = stoi(operands[2].substr(1));
    int rs2 = stoi(operands[3].substr(1));

    bitset<32> rs1_val(registers[rs1]);
    bitset<32> rs2_val(registers[rs2]);
    bitset<32> result = rs1_val ^ rs2_val;
    registers[rd] = result.to_ulong();
}
void srli(const vector<string> operands) {
    int rd = stoi(operands[1].substr(1));
    int rs1 = stoi(operands[2].substr(1));
    int shamt = stoi(operands[3]);

    registers[rd] = registers[rs1] >> shamt;
}
void sltui(const vector<string> operands) {
    int rd = stoi(operands[1].substr(1));
    int rs1 = stoi(operands[2].substr(1));
    int imm = stoi(operands[3]);

    registers[rd] = ((int)registers[rs1] < imm) ? 1 : 0;
}
void ori(const vector<string> operands) {
    int rd = stoi(operands[1].substr(1));
    int rs1 = stoi(operands[2].substr(1));
    int imm = stoi(operands[3]);

    registers[rd] = registers[rs1] | imm;
}
void andi(const vector<string> operands) {
    int rd = stoi(operands[1].substr(1));
    int rs1 = stoi(operands[2].substr(1));
    int imm = stoi(operands[3]);

    registers[rd] = registers[rs1] & imm;
}
void xori(const vector<string> operands) {
    int rd = stoi(operands[1].substr(1));
    int rs1 = stoi(operands[2].substr(1));
    int imm = stoi(operands[3]);

    registers[rd] = registers[rs1] ^ imm;
}
void sltu(const vector<string> operands) {
    int rd = stoi(operands[1].substr(1));
    int rs1 = stoi(operands[2].substr(1));
    int rs2 = stoi(operands[3].substr(1));

    registers[rd] = (registers[rs1] < registers[rs2]) ? 1 : 0;
}
void sll(const vector<string> operands) {
    int rd = stoi(operands[1].substr(1));
    int rs1 = stoi(operands[2].substr(1));
    int shamt = stoi(operands[3]);

    registers[rd] = registers[rs1] << shamt;
}
void srl(const vector<string> operands) {
    int rd = stoi(operands[1].substr(1));
    int rs1 = stoi(operands[2].substr(1));
    int shamt = stoi(operands[3]);

    registers[rd] = registers[rs1] >> shamt;
}
void sra(const vector<string> operands) {
    int rd = stoi(operands[1].substr(1));
    int rs1 = stoi(operands[2].substr(1));
    int shamt = stoi(operands[3]);

    registers[rd] = ((int32_t)registers[rs1]) >> shamt;
}

void lw(string  operands) {
   istringstream iss(operands);
    vector<std::string> tokens;
    string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    string instructionName = tokens[0];
    int destinationRegister = stoi(tokens[1].substr(1, tokens[1].size()-1));
    string thirdToken = tokens[2];
    size_t openParenthesisPos = thirdToken.find('(');
    size_t closeParenthesisPos = thirdToken.find(')');
    string immediateValue = thirdToken.substr(0, openParenthesisPos);
    int sourceRegister = stoi(thirdToken.substr(openParenthesisPos + 2, closeParenthesisPos - openParenthesisPos - 1));
    int imm = stoi(immediateValue) + registers[sourceRegister];
    int value= memory[imm];
      registers[destinationRegister]=value;

}
void lh(string operands) {
    cout<<operands<<endl;
    istringstream iss(operands);
    vector<std::string> tokens;
    string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    string instructionName = tokens[0];
    int destinationRegister = stoi(tokens[1].substr(1, tokens[1].size()-1));
    string thirdToken = tokens[2];
    size_t openParenthesisPos = thirdToken.find('(');
    size_t closeParenthesisPos = thirdToken.find(')');
    string immediateValue = thirdToken.substr(0, openParenthesisPos);
    int sourceRegister = stoi(thirdToken.substr(openParenthesisPos + 2, closeParenthesisPos - openParenthesisPos - 1));
    int imm = stoi(immediateValue) + registers[sourceRegister];
    int value= memory[imm];
    string take = decimalToBinary(value);
    string without= take.substr(16, 16);
    cout<<without<<endl;
    if (without[0]=='0')
    {
        string zeros="0000000000000000";
        without =(zeros+without);
    }
    else if(without[0]=='1')
    {
       string ones="1111111111111111";
        without =(ones+without);
    }
    cout<<without<<endl;
    int with= binaryToDecimal(without);
    cout<<with;
    registers[destinationRegister]=with;
   
}
void lhu(string operands) {
    cout<<operands<<endl;
    istringstream iss(operands);
    vector<std::string> tokens;
    string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    string instructionName = tokens[0];
    int destinationRegister = stoi(tokens[1].substr(1, tokens[1].size()-1));
    string thirdToken = tokens[2];
    size_t openParenthesisPos = thirdToken.find('(');
    size_t closeParenthesisPos = thirdToken.find(')');
    string immediateValue = thirdToken.substr(0, openParenthesisPos);
    int sourceRegister = stoi(thirdToken.substr(openParenthesisPos + 2, closeParenthesisPos - openParenthesisPos - 1));
    int imm = stoi(immediateValue) + registers[sourceRegister];
    int value= memory[imm];
    string take = decimalToBinary(value);
    string without= take.substr(16, 16);
    cout<<without<<endl;
        string zeros="0000000000000000";
        without =(zeros+without);
    cout<<without<<endl;
    int with= binaryToDecimal(without);
    cout<<with;
    registers[destinationRegister]=with;
   
}

void sw(uint32_t data, int offset) {
    
    memory[offset] = data;
}
int jalr( const vector<string> operands, int PC) {

    int rd = stoi(operands[1].substr(1));
    int rs1 = stoi(operands[2].substr(1));
    int imm = stoi(operands[3]);
    registers[rd]=PC+4;
    int p;
    return p = registers[rs1]+imm;
}
void sh(uint16_t data, int offset) {
  int addr = address + offset;
  
  uint16_t* mem_ptr = reinterpret_cast<uint16_t*>(&memory[addr / 4]);
  *mem_ptr = data;
    
}
void auipc(const vector<string> operands) {
    int rd = stoi(operands[1].substr(1));
    int immediate = stoi(operands[2]);
    registers[rd] = (PC-4) + (immediate<<12);
}
void sb(uint8_t value, uint32_t address) {
    memory[address] = value;
}
void lb(string operands) {
    cout<<operands<<endl;
    istringstream iss(operands);
    vector<std::string> tokens;
    string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    string instructionName = tokens[0];
    int destinationRegister = stoi(tokens[1].substr(1, tokens[1].size()-1));
    string thirdToken = tokens[2];
    size_t openParenthesisPos = thirdToken.find('(');
    size_t closeParenthesisPos = thirdToken.find(')');
    string immediateValue = thirdToken.substr(0, openParenthesisPos);
    int sourceRegister = stoi(thirdToken.substr(openParenthesisPos + 2, closeParenthesisPos - openParenthesisPos - 1));
    int imm = stoi(immediateValue) + registers[sourceRegister];
    int value= memory[imm];
    string take = decimalToBinary(value);
    string without= take.substr(24, 8);
    if (without[0]=='0')
    {
        string zeros="000000000000000000000000";
        without =(zeros+without);
    }
    else if(without[0]=='1')
    {
       string ones="111111111111111111111111";
        without =(ones+without);
    }
   
    int with= binaryToDecimal(without);
    registers[destinationRegister]=with;
   
}
void lbu(string operands) {
    cout<<operands<<endl;
    istringstream iss(operands);
    vector<std::string> tokens;
    string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    string instructionName = tokens[0];
    int destinationRegister = stoi(tokens[1].substr(1, tokens[1].size()-1));
    string thirdToken = tokens[2];
    size_t openParenthesisPos = thirdToken.find('(');
    size_t closeParenthesisPos = thirdToken.find(')');
    string immediateValue = thirdToken.substr(0, openParenthesisPos);
    int sourceRegister = stoi(thirdToken.substr(openParenthesisPos + 2, closeParenthesisPos - openParenthesisPos - 1));
    int imm = stoi(immediateValue) + registers[sourceRegister];
    int value= memory[imm];
    string take = decimalToBinary(value);
    string without= take.substr(24, 8);
        string zeros="000000000000000000000000";
        without =(zeros+without);
    int with= binaryToDecimal(without);
    registers[destinationRegister]=with;
   
}

void lui(int reg_num, int immediate) {
  
    registers[reg_num] = immediate << 12;
}
