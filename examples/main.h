#include "openai.hpp"
#include<string>
#include<vector>
using namespace std;

struct data {
	string name;
};

struct select {
	struct data cpu;
	struct data gpu;
	struct data ram;
	struct data board;
	struct data storage;
};

class CPU {
protected:
	int cpu_price;
	vector<struct data> cpu_spec;
public:
	int get_cpu_price() {
		return cpu_price;
	}
	void set_cpu_price(int price_in) {
		cpu_price = price_in;
	}
	struct data get_cpu_spec(int pos) {
		return cpu_spec[pos];
	}
	void set_cpu_spec(struct data spec_in) {
		cpu_spec.push_back(spec_in);
	}
};

class GPU {
protected:
	int gpu_price;
	vector<struct data> gpu_spec;
public:
	int get_gpu_price() {
		return gpu_price;
	}
	void set_gpu_price(int price_in) {
		gpu_price = price_in;
	}
	struct data get_gpu_spec(int pos) {
		return gpu_spec[pos];
	}
	void set_gpu_spec(struct data spec_in) {
		gpu_spec.push_back(spec_in);
	}
};

class RAM {
protected:
	int ram_price;
	vector<struct data> ram_spec;
public:
	int get_ram_price() {
		return ram_price;
	}
	void set_ram_price(int price_in) {
		ram_price = price_in;
	}
	struct data get_ram_spec(int pos) {
		return ram_spec[pos];
	}
	void set_ram_spec(struct data spec_in) {
		ram_spec.push_back(spec_in);
	}
};

class BOARD {
protected:
	int board_price;
	vector<struct data> board_spec;
public:
	int get_board_price() {
		return board_price;
	}
	void set_board_price(int price_in) {
		board_price = price_in;
	}
	struct data get_board_spec(int pos) {
		return board_spec[pos];
	}
	void set_board_spec(struct data spec_in) {
		board_spec.push_back(spec_in);
	}
};

class STORAGE {
protected:
	int storage_price;
	vector<struct data> storage_spec;
public:
	int get_storage_price() {
		return storage_price;
	}
	void set_storage_price(int price_in) {
		storage_price = price_in;
	}
	struct data get_storage_spec(int pos) {
		return storage_spec[pos];
	}
	void set_storage_spec(struct data spec_in) {
		storage_spec.push_back(spec_in);
	}
};

class USER : public CPU, GPU, RAM, BOARD, STORAGE {
private:
	int budget;
	string purpose;
	struct select selected;

public:
	int get_budget() {
		return budget;
	}
	void set_budget(int budget_in) {
		budget = budget_in;
	}
	string get_purpose() {
		return purpose;
	}
	void set_purpose(string purpose_in) {
		purpose = purpose_in;
	}
	void select_cpu(struct data data_in) {
		selected.cpu = data_in;
	}
	void select_gpu(struct data data_in) {
		selected.gpu = data_in;
	}
	void select_ram(struct data data_in) {
		selected.ram = data_in;
	}
	void select_board(struct data data_in) {
		selected.board = data_in;
	}
	void select_storage(struct data data_in) {
		selected.storage = data_in;
	}
	struct data get_cpu_spec() {
		return selected.cpu;
	}
	struct data get_gpu_spec() {
		return selected.gpu;
	}
	struct data get_ram_spec() {
		return selected.ram;
	}
	struct data get_board_spec() {
		return selected.board;
	}
	struct data get_storage_spec() {
		return selected.storage;
	}
};

class API {
public:
	nlohmann::json api_ret(nlohmann::json requestData) {
		return openai::chat().create(requestData);
	}
};
