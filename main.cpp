//  main.cpp
//  ProjectAssembly
//
//  Created by muhammad abdelmohsen on 03/05/2023.
//

#include <iostream>
#include<fstream>
#include<map>
#include<vector>
#include<string>
#include<sstream>
#include<bitset>

using namespace std;

// Example RISC-V memory map
// Memory is a 32-bit address space
// with 32-bit words stored at each address
#define MEM_SIZE 2056
int memory[MEM_SIZE];

map<unsigned int, string> AddressInst;
map<string, unsigned int> AddressLabel;
map<int,string>InstructionMem;
map<int, int> registers;
map<string, int> labels;
int PC = 0;
int reg_num = 31;
int address=0x100;



map<int, int> initialize_registers() {
    ifstream file("/Users/muhammadabdelmohsen/Desktop/assemblyproj/registers.txt");
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

//void checkLabelExists(string label){
//    if(AdressLabel.find(label) ==AdressLabel.end()){
//        cout<<"You are trying to jump to a label that does not exist. The program will terminate\n";
//        system("pause");
//        exit(1);
//    }
//}

void Printregs(map<int, int> registers){
    // Print out the register values
    for (int i = 0; i < registers.size(); i++) {
        int reg_num = i;
        int value = registers[reg_num];
        cout << "x"<< reg_num << " = " << value << endl;
    }
    
}


void addi(const vector<string> operands, map<int, int>& registers) {
    int rd = stoi(operands[1].substr(1));
    int rs1 = stoi(operands[2].substr(1));
    int imm = stoi(operands[3]);

    registers[rd] = registers[rs1] + imm;
}

void add(const vector<string> operands, map<int, int>& registers) {
    int rd = stoi(operands[1].substr(1));
    int rs1 = stoi(operands[2].substr(1));
    int rs2 = stoi(operands[3].substr(1));

    registers[rd] = registers[rs1] + registers[rs2];
}
void sub(const vector<string> operands, map<int, int>& registers) {
    int rd = stoi(operands[1].substr(1));
    int rs1 = stoi(operands[2].substr(1));
    int rs2 = stoi(operands[3].substr(1));

    registers[rd] = registers[rs1] - registers[rs2];
}

void srai(const vector<string> operands, map<int, int>& registers) {
    int rd = stoi(operands[1].substr(1));
    int rs1 = stoi(operands[2].substr(1));
    int imm = stoi(operands[3]);

    registers[rd] = ((int32_t)registers[rs1]) >> imm;
}


void slli(const vector<string> operands, map<int, int>& registers) {
    int rd = stoi(operands[1].substr(1));
    int rs1 = stoi(operands[2].substr(1));
    int shamt = stoi(operands[3]);

    registers[rd] = registers[rs1] << shamt;
}

void and_func(const vector<string> operands, map<int, int>& registers) {
    int rd = stoi(operands[1].substr(1));
    int rs1 = stoi(operands[2].substr(1));
    int rs2 = stoi(operands[3].substr(1));

    bitset<32> rs1_val(registers[rs1]);
    bitset<32> rs2_val(registers[rs2]);
    bitset<32> result = rs1_val & rs2_val;
    registers[rd] = result.to_ulong();
}
void or_func(const vector<string> operands, map<int, int>& registers) {
    int rd = stoi(operands[1].substr(1));
    int rs1 = stoi(operands[2].substr(1));
    int rs2 = stoi(operands[3].substr(1));

    bitset<32> rs1_val(registers[rs1]);
    bitset<32> rs2_val(registers[rs2]);
    bitset<32> result = rs1_val | rs2_val;
    registers[rd] = result.to_ulong();
}

void xor_func(const vector<string> operands, map<int, int>& registers) {
    int rd = stoi(operands[1].substr(1));
    int rs1 = stoi(operands[2].substr(1));
    int rs2 = stoi(operands[3].substr(1));

    bitset<32> rs1_val(registers[rs1]);
    bitset<32> rs2_val(registers[rs2]);
    bitset<32> result = rs1_val ^ rs2_val;
    registers[rd] = result.to_ulong();
}
void srli(const vector<string> operands, map<int, int>& registers) {
    int rd = stoi(operands[1].substr(1));
    int rs1 = stoi(operands[2].substr(1));
    int shamt = stoi(operands[3]);

    registers[rd] = registers[rs1] >> shamt;
}

void sltui(const vector<string> operands, map<int, int>& registers) {
    int rd = stoi(operands[1].substr(1));
    int rs1 = stoi(operands[2].substr(1));
    int imm = stoi(operands[3]);

    registers[rd] = ((int)registers[rs1] < imm) ? 1 : 0;
}

void ori(const vector<string> operands, map<int, int>& registers) {
    int rd = stoi(operands[1].substr(1));
    int rs1 = stoi(operands[2].substr(1));
    int imm = stoi(operands[3]);

    registers[rd] = registers[rs1] | imm;
}
void andi(const vector<string> operands, map<int, int>& registers) {
    int rd = stoi(operands[1].substr(1));
    int rs1 = stoi(operands[2].substr(1));
    int imm = stoi(operands[3]);

    registers[rd] = registers[rs1] & imm;
}

void xori(const vector<string> operands, map<int, int>& registers) {
    int rd = stoi(operands[1].substr(1));
    int rs1 = stoi(operands[2].substr(1));
    int imm = stoi(operands[3]);

    registers[rd] = registers[rs1] ^ imm;
}

void sltu(const vector<string> operands, map<int, int>& registers) {
    int rd = stoi(operands[1].substr(1));
    int rs1 = stoi(operands[2].substr(1));
    int rs2 = stoi(operands[3].substr(1));

    registers[rd] = (registers[rs1] < registers[rs2]) ? 1 : 0;
}

void sll(const vector<string> operands, map<int, int>& registers) {
    int rd = stoi(operands[1].substr(1));
    int rs1 = stoi(operands[2].substr(1));
    int shamt = stoi(operands[3]);

    registers[rd] = registers[rs1] << shamt;
}

void srl(const vector<string> operands, map<int, int>& registers) {
    int rd = stoi(operands[1].substr(1));
    int rs1 = stoi(operands[2].substr(1));
    int shamt = stoi(operands[3]);

    registers[rd] = registers[rs1] >> shamt;
}

void sra(const vector<string> operands, map<int, int>& registers) {
    int rd = stoi(operands[1].substr(1));
    int rs1 = stoi(operands[2].substr(1));
    int shamt = stoi(operands[3]);

    registers[rd] = ((int32_t)registers[rs1]) >> shamt;

}
// Load immediate (li) instruction
void li(int reg_num, int immediate, map<int, int>& registers) {
    registers[reg_num] = immediate;
}
int lw(int offset) {
  // Convert address to pointer with offset
  int* mem_ptr = &memory[(address + offset)/4];
  // Load data from memory and return
    return *mem_ptr ;
}
int lh(int offset) {
  // Convert address to pointer with offset
  short* mem_ptr = (short*) &memory[(address + offset) / 4];
  // Load data from memory and return
  return (int) *mem_ptr;
}

//void lh (int rd, int rs1, int imm)
//{
//    if (rd == 0)
//    {
//        return;
//
//    } else
//
//    {
//        int r = (registers[rs1] + imm) % 4;
//        int address = registers[rs1] + imm - r;
//
//
//
//            registers[rd] = (memory[address] << (8 * (2 - r))) >> 16;
//        }
//
//
//    PC += 4;
//}


void sw(uint32_t data, int offset) {
  // Convert address to pointer with offset
  int* mem_ptr = &memory[(address + offset)/4];
  // Store data to memory
  *mem_ptr = data;
}
void sh(uint16_t data, int offset) {
  int addr = address + offset;
  // Check that the address is aligned to a half-word boundary
  // Convert address to pointer with offset
  uint16_t* mem_ptr = reinterpret_cast<uint16_t*>(&memory[addr / 4]);
  // Store half-word data to memory
  *mem_ptr = data;
}

void sb(uint8_t value, uint32_t address) {
    memory[address] = value;
}

int lb(uint32_t address) {
    int8_t byte = memory[address];
    return byte;
}

void lui(int reg_num, int immediate, map<int, int>& registers) {
    // LUI sets the upper 20 bits of the destination register
    registers[reg_num] = immediate << 12;
}




void ReadAndExecute(map<int, int>& registers) {
    ifstream file("/Users/muhammadabdelmohsen/Desktop/assemblyproj/instructions.txt");
    string Line;
    int PC = 0;
    int Counterr=1;
    
    while (!file.eof()) {
        // Parse operands from instruction
        getline(file, Line);
        istringstream iss(Line);
        vector<string> operands;
        for (string operand; iss >> operand; ) {
            operands.push_back(operand);
            InstructionMem[address]=Line;
            address=+4;
        }
       
        // Check for label and add it to the map
        if (operands[0].back() == ':') {
            labels[operands[0].substr(0, operands[0].size()-1)] = PC;
            continue;
        }
        // Check for branch instructions and calculate the target address
        if (operands[0] == "lw") {
            int address = stoi(operands[2]);
            int value = lw(address);
            int reg_num = stoi(operands[1].substr(1));
            registers[reg_num] = value;
            PC += 4;
        } else if (operands[0] == "lh") {
            int address = stoi(operands[2]);
            int value = lh(address);
            int reg_num = stoi(operands[1].substr(1));
            registers[reg_num] = value;
            PC += 4;
        } else if (operands[0] == "sh") {
            int address = stoi(operands[2]);
            int reg_num = stoi(operands[1].substr(1));
            int value = registers[reg_num];
            sh(static_cast<uint16_t>(value), address);
            PC += 4;
          }else if (operands[0] == "sw") {
            int address = stoi(operands[2]);
            int reg_num = stoi(operands[1].substr(1));
            int value = registers[reg_num];
            sw(value, address);
            PC += 4;
            
        } // Check for load immediate (li) instruction and execute it
        else if (operands[0] == "li") {
            int reg_num = stoi(operands[1].substr(1));
            int immediate = stoi(operands[2]);
            li(reg_num, immediate, registers);
            PC += 4;
    } else if (operands[0] == "lb") {
        int address = stoi(operands[2]);
        int reg_num = stoi(operands[1].substr(1));
        int value = lb(address);
        registers[reg_num] = value;
        PC += 4;
    } else if (operands[0] == "sb") {
        int address = stoi(operands[2]);
        int reg_num = stoi(operands[1].substr(1));
        int8_t value = registers[reg_num] & 0xff;
        sb(value, address);
        PC += 4;
    }
        else if (operands[0] == "addi") {
            addi(operands, registers);
            PC += 4;
        } else if (operands[0] == "add") {
            add(operands, registers);
            PC += 4;
        } else if (operands[0] == "sub") {
            sub(operands, registers);
            PC += 4;
        } else if (operands[0] == "or") {
            or_func(operands, registers);
            PC += 4;
        } else if (operands[0] == "xor") {
            xor_func(operands, registers);
            PC += 4;
        } else if (operands[0] == "and") {
            and_func(operands, registers);
            PC += 4;
        } else if (operands[0] == "slli") {
            slli(operands, registers);
            PC += 4;
        } else if (operands[0] == "srai") {
            srai(operands, registers);
            PC += 4;
        } else if (operands[0] == "sra") {
            sra(operands, registers);
            PC += 4;
        } else if (operands[0] == "srl") {
            srl(operands, registers);
            PC += 4;
        } else if (operands[0] == "sll") {
            sll(operands, registers);
            PC += 4;
        } else if (operands[0] == "sltu") {
            sltu(operands, registers);
            PC += 4;
        } else if (operands[0] == "xori") {
            xori(operands, registers);
            PC +=4;
        } else if (operands[0] == "ori") {
            ori(operands, registers);
            PC += 4;
        } else if (operands[0] == "sltui") {
            sltui(operands, registers);
            PC += 4;
        } else if (operands[0] == "srli") {
            srli(operands, registers);
            PC += 4;
//        } else if (operands[0] == "j") {
//            string label_name = operands[1];
//            jump(label_name, PC);
//        } else if (operands[0] == "bne") {
//            bne(stoi(operands[1]), stoi(operands[2]), operands[3], PC, labels);
        } else if (operands[0] == "lui") {
            int reg_num = stoi(operands[1].substr(1));
            int immediate = stoi(operands[2]);
            lui(reg_num, immediate, registers);
            PC += 4;
        }
        cout<<"The registers after "<<Counterr<<" Instruction ="<<"\n";
        Printregs(registers);
        Counterr++;
    }
    cout<<"The program Counter: "<<PC<<"\n";
}
int main(){
    
    map<string, int> labels;
    map<int, int> registers = initialize_registers();
    ReadAndExecute(registers);

}
