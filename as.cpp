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
#define MEM_SIZE 1024
uint32_t memory[MEM_SIZE];
map<unsigned int, string> AdressInst;
map<string, unsigned int> AdressLabel;
map<int, int> registers;
map<string, int> labels;
 int PC = 0;
 int reg_num = 31;
int address=0x100;



map<int, int> initialize_registers() {
    ifstream file("C:/AUC/AUC sixth semester/Assembly/registers.txt");
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

void checkLabelExists(string label){
    if(AdressLabel.find(label) ==AdressLabel.end()){
        cout<<"You are trying to jump to a label that does not exist. The program will terminate\n";
        system("pause");
        exit(1);
    }
}

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
void jump(const string label_name, int &PC) {
    // Get the address of the label from the AdressLabel map
    unsigned int label_addr = AdressLabel[label_name];

    // Set the PC to the address of the label
    PC = label_addr;
}
void jumping(string label, int& pc, map<string, int>& labels) {
    // Jump to the label if it exists in the labels map
    if (labels.find(label) != labels.end()) {
        pc = labels[label];
    } else {
        cout << "Error: Label " << label << " not found." << endl;
        exit(1);
    }
}

void bne(int rs1, int rs2, string label, int& pc, map<string, int>& labels) {
    if (rs1 != rs2) {
        // Jump to the label if the branch is satisfied
        jumping(label, pc, labels);
    } else {
        // Do not jump to the label if the branch is not satisfied
        pc += 4;
    }
}
// Load immediate (li) instruction
void li(int reg_num, int immediate, map<int, int>& registers) {
    registers[reg_num] = immediate;
}
int lw() {
  // Convert address to pointer
  uint32_t* mem_ptr = &memory[address/4];
  // Load data from memory and return
  return *mem_ptr;
}

void sw(uint32_t data) {
  // Convert address to pointer
  uint32_t* mem_ptr = &memory[address/4];
  // Store data to memory
  *mem_ptr = data;
}



void ReadAndExecute(map<int, int>& registers) {
    ifstream file("C:/AUC/AUC sixth semester/Assembly/instructions.txt");
    string String;
    int PC = 0;
    int Counterr=1;
    
    while (!file.eof()) {
        getline(file, String);
        // Parse operands from instruction
        istringstream iss(String);
        vector<string> operands;
       
        for (string operand; iss >> operand; ) {
            operands.push_back(operand);
        }
        // Check for label and add it to the map
        if (operands[0].back() == ':') {
            labels[operands[0].substr(0, operands[0].size()-1)] = PC;
            continue;
        }
        // Check for branch instructions and calculate the target address
        else if (operands[0] == "lw") {
            uint32_t address = stoi(operands[2]);
            uint32_t value = lw();
            int reg_num = stoi(operands[1].substr(1));
            registers[reg_num] = value;
            PC += 4;
        } else if (operands[0] == "sw") {
            address = stoi(operands[2]);
            int reg_num = stoi(operands[1].substr(1));
            uint32_t value = registers[reg_num];
            sw(value);
            PC += 4;
        } // Check for load immediate (li) instruction and execute it
        else if (operands[0] == "li") {
            int reg_num = stoi(operands[1].substr(1));
            int immediate = stoi(operands[2]);
            li(reg_num, immediate, registers);
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
        } else if (operands[0] == "j") {
            string label_name = operands[1];
            jump(label_name, PC);
        } else if (operands[0] == "bne") {
            bne(stoi(operands[1]), stoi(operands[2]), operands[3], PC, labels);
        }
        cout<<"The registers after "<<Counterr<<" Instruction ="<<"\n";
        Printregs(registers);
        Counterr++;
    }
   // cout<<"The registers after "<<Counterr<<" Instruction ="<<"\n";
   // Printregs(registers);
    cout<<"The program Counter: "<<PC<<"\n";



    
}




int main(){
    
    map<string, int> labels;
    map<int, int> registers = initialize_registers();
    ReadAndExecute(registers);
}