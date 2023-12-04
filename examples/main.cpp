#include "openai.hpp"
#include "main.h"
#include<iostream>
#include<string>
using namespace std;

int main() {
	openai::start();
	API api;
	USER user;
	CPU cpu;
	GPU gpu;
	RAM ram;
	BOARD board;
	STORAGE storage;
	
	int budget_in;
	string purpose_in;
	cout << "예산 : ";
	cin >> budget_in;
	user.set_budget(budget_in);
	cout << "사용 목적 : ";
	cin >> purpose_in;
	user.set_purpose(purpose_in);
	
	string question = "\"컴퓨터를 사려고 하는데 목적은 다음과 같아.\n목적 : " + user.get_purpose() + "\nCPU, GPU, RAM, 메인보드, 스토리지의 가격 비중을 % 단위로 추천해줘.\n\'항목 : ~%\'의 형식으로 답변해줘.";
	nlohmann::json requestData = R"(
	{
		"model" : "gpt-3.5-turbo",
		"messages" : [{"role" : "user"}]
	}
	)"_json;
	requestData["messages"][0]["content"] = question;
	string answer = api.api_ret(requestData)["choices"][0]["message"]["content"].get<string>();	
	cout << answer << '\n';

	size_t found = answer.find('%');
	int cnt = 0;
	int price[5];
	while(found != string::npos && cnt < 5)
	{
		price[cnt] = answer[found - 1] - '0';
		if(answer[found - 2] >= '0' && answer[found - 2] <= '9')
			price[cnt] += (answer[found - 2] - '0') * 10;
		price[cnt] = (int)((double)user.get_budget() / 100 * price[cnt]);
		found = answer.find('%', found + 1);
		cnt++;
	}
	cpu.set_cpu_price(price[0]);
	gpu.set_gpu_price(price[1]);
	ram.set_ram_price(price[2]);
	board.set_board_price(price[3]);
	storage.set_storage_price(price[4]);

	struct data spec;

	requestData["messages"][0]["content"] = "\"CPU" + to_string(cpu.get_cpu_price()) + "만원대의 제품명을 이름만 3개만 추천해줘.\"";
	answer = api.api_ret(requestData)["choices"][0]["message"]["content"].get<string>();
	cout << "CPU : " + to_string(cpu.get_cpu_price()) + "만원대\n";
	cout << answer << "\n\n";
	
	size_t found1 = answer.find('.');
	size_t found2 = answer.find('\n');
	cnt = 0;
	while(found1 != string::npos && cnt < 3)
	{
		spec.name = answer.substr(found1 + 2, found2 - found1 - 2);
		found1 = answer.find('.', found2 + 1);
		found2 = answer.find('\n', found2 + 1);
		cpu.set_cpu_spec(spec);
		cnt++;
	}

	
	requestData["messages"][0]["content"] = "\"GPU" + to_string(gpu.get_gpu_price()) + "만원대의 제품명을 이름만 3개만 추천해줘.\"";
	answer = api.api_ret(requestData)["choices"][0]["message"]["content"].get<string>();
	cout << "GPU : " + to_string(gpu.get_gpu_price()) + "만원대\n";
	cout << answer << "\n\n";
	
	found1 = answer.find('.');
	found2 = answer.find('\n');
	cnt = 0;
	while(found1 != string::npos && cnt < 3)
	{
		spec.name = answer.substr(found1 + 2, found2 - found1 - 2);
		found1 = answer.find('.', found2 + 1);
		found2 = answer.find('\n', found2 + 1);
		gpu.set_gpu_spec(spec);
		cnt++;
	}

	requestData["messages"][0]["content"] = "\"RAM" + to_string(ram.get_ram_price()) + "만원대의 제품명을 이름만 3개만 추천해줘.\"";
	answer = api.api_ret(requestData)["choices"][0]["message"]["content"].get<string>();
	cout << "RAM : " + to_string(ram.get_ram_price()) + "만원대\n";
	cout << answer << "\n\n";

	found1 = answer.find('.');
	found2 = answer.find('\n');
	cnt = 0;
	while(found1 != string::npos && cnt < 3)
	{
		spec.name = answer.substr(found1 + 2, found2 - found1 - 2);
		found1 = answer.find('.', found2 + 1);
		found2 = answer.find('\n', found2 + 1);
		ram.set_ram_spec(spec);
		cnt++;
	}

	requestData["messages"][0]["content"] = "\"메인보드" + to_string(board.get_board_price()) + "만원대의 제품명을 이름만 3개만 추천해줘.\"";
	answer = api.api_ret(requestData)["choices"][0]["message"]["content"].get<string>();
	cout << "메인보드 : " + to_string(board.get_board_price()) + "만원대\n";
	cout << answer << "\n\n";

	found1 = answer.find('.');
	found2 = answer.find('\n');
	cnt = 0;
	while(found1 != string::npos && cnt < 3)
	{
		spec.name = answer.substr(found1 + 2, found2 - found1 - 2);
		found1 = answer.find('.', found2 + 1);
		found2 = answer.find('\n', found2 + 1);
		board.set_board_spec(spec);
		cnt++;
	}

	requestData["messages"][0]["content"] = "\"스토리지" + to_string(storage.get_storage_price()) + "만원대의 제품명을 이름만 3개만 추천해줘.\"";
	answer = api.api_ret(requestData)["choices"][0]["message"]["content"].get<string>();
	cout << "스토리지 : " + to_string(storage.get_storage_price()) + "만원대\n";
	cout << answer << "\n\n";

	found1 = answer.find('.');
	found2 = answer.find('\n');
	cnt = 0;
	while(found1 != string::npos && cnt < 3)
	{
		spec.name = answer.substr(found1 + 2, found2 - found1 - 2);
		found1 = answer.find('.', found2 + 1);
		found2 = answer.find('\n', found2 + 1);
		storage.set_storage_spec(spec);
		cnt++;
	}

	
	int num,sel,i;
	
	for(i=0;i<5;i++)
	{
		cout << " 어떤 방식으로 장비를 선택 하시겠습니까?\n";
		cout << "1. 장비 직접 선택\n";
		cout << "2. 장비 추천\n";
		if(i==0)
		cout << "3. 원하는 장비 선택시 나머지 장비는 이에 맞춰 추천\n";
		
		cin >>sel;
		if(sel==1)
		{
			if(i==0)
			{
				cout << "CPU를 선택해주세요 : ";
				cin >> num;
				user.select_cpu(cpu.get_cpu_spec(num - 1));
			}
			else if(i==1)
			{
				cout << "GPU를 선택해주세요 : ";
				cin >> num;
				user.select_gpu(gpu.get_gpu_spec(num - 1));
			}
			else if(i==2)
			{
				cout << "RAM을 선택해주세요 : ";
				cin >> num;
				user.select_ram(ram.get_ram_spec(num - 1));
			}
			else if(i==3)
			{
				cout << "메인보드를 선택해주세요 : ";
				cin >> num;
				user.select_board(board.get_board_spec(num - 1));
			}
			else if(i==4)
			{
				cout << "스토리지를 선택해주세요 : ";
				cin >> num;
				user.select_storage(storage.get_storage_spec(num - 1));
			}

		}
		else if(sel==2)
		{
			struct data datas[3];
			if (i == 0)
			{
				datas[0].name = cpu.get_cpu_spec(0).name;
				datas[1].name = cpu.get_cpu_spec(1).name;
				datas[2].name = cpu.get_cpu_spec(2).name;
			}
			else if (i == 1)
			{
				datas[0].name = gpu.get_gpu_spec(0).name;
				datas[1].name = gpu.get_gpu_spec(1).name;
				datas[2].name = gpu.get_gpu_spec(2).name;
			}
			else if (i == 2)
			{
				datas[0].name = ram.get_ram_spec(0).name;
				datas[1].name = ram.get_ram_spec(1).name;
				datas[2].name = ram.get_ram_spec(2).name;
			}
			else if (i == 3)
			{
				datas[0].name = board.get_board_spec(0).name;
				datas[1].name = board.get_board_spec(1).name;
				datas[2].name = board.get_board_spec(2).name;
			}
			else if (i == 4) 
			{
				datas[0].name = storage.get_storage_spec(0).name;
				datas[1].name = storage.get_storage_spec(1).name;
				datas[2].name = storage.get_storage_spec(2).name;
			}
			question = "\"" + datas[0].name + ", " + datas[1].name  + ", " + datas[2].name + "중 하나만 골라줘.\n목적은 다음과 같아.\n목적 : " + user.get_purpose() + "\"";
			nlohmann::json requestData = R"(
			{
				"model" : "gpt-3.5-turbo",
				"messages" : [{"role" : "user"}]
			}
			)"_json;
			requestData["messages"][0]["content"] = question;
			string answer = api.api_ret(requestData)["choices"][0]["message"]["content"].get<string>();
			cout << answer << '\n';
			for (int j = 0; j < 3; j++)
			{
				if (answer.find(datas[j].name) == string::npos) continue;
				if (i == 0) user.select_cpu(datas[j]);
				else if (i == 1) user.select_gpu(datas[j]);
				else if (i == 2) user.select_ram(datas[j]);
				else if (i == 3) user.select_board(datas[j]);
				else if (i == 4) user.select_storage(datas[j]);
				break;
			}
		}
		else
		{
			char arr[5] = {'c', 'g', 'r', 'b', 's'};
			int wantnum;
			char wantchar;
			cout<< "선택하고 싶은 장비를 고르세요(장비 문자, 장비 번호)\n";
			cin >> wantchar;
			cin >> wantnum;

			struct data selected;
			if (wantchar == 'c')
			{
				selected = cpu.get_cpu_spec(wantnum - 1);
				user.select_cpu(selected);
			}
			else if (wantchar == 'g')
			{
				selected = gpu.get_gpu_spec(wantnum - 1);
				user.select_gpu(selected);
			}
			else if (wantchar == 'r')
			{
				selected = ram.get_ram_spec(wantnum - 1);
				user.select_ram(selected);
			}
			else if (wantchar == 'b')
			{
				selected = board.get_board_spec(wantnum - 1);
				user.select_board(selected);
			}
			else if (wantchar == 's')
			{
				selected = storage.get_storage_spec(wantnum - 1);
				user.select_storage(selected);
			}

			for (int j = 0; j < 5; j++)
			{
				if (arr[j] == wantchar) continue;
				struct data datas[3];
				if (j == 0)
				{
					datas[0].name = cpu.get_cpu_spec(0).name;
					datas[1].name = cpu.get_cpu_spec(1).name;
					datas[2].name = cpu.get_cpu_spec(2).name;
				}
				else if (j == 1)
				{
					datas[0].name = gpu.get_gpu_spec(0).name;
					datas[1].name = gpu.get_gpu_spec(1).name;
					datas[2].name = gpu.get_gpu_spec(2).name;
				}
				else if (j == 2)
				{
					datas[0].name = ram.get_ram_spec(0).name;
					datas[1].name = ram.get_ram_spec(1).name;
					datas[2].name = ram.get_ram_spec(2).name;
				}
				else if (j == 3)
				{
					datas[0].name = board.get_board_spec(0).name;
					datas[1].name = board.get_board_spec(1).name;
					datas[2].name = board.get_board_spec(2).name;
				}
				else if (j == 4)
				{
					datas[0].name = storage.get_storage_spec(0).name;
					datas[1].name = storage.get_storage_spec(1).name;
					datas[2].name = storage.get_storage_spec(2).name;
				}
				question = "\"" + datas[0].name + ", " + datas[1].name + ", " + datas[2].name + "중 하나만 골라줘.\n다음 장비와 가장 어울리는 제품을 골라야 해.\n" + selected.name + "\n첫 번째 줄에 그 제품의 이름만 적어줘.\"";
				nlohmann::json requestData = R"(
				{
					"model" : "gpt-3.5-turbo",
					"messages" : [{"role" : "user"}]
				}
				)"_json;
				requestData["messages"][0]["content"] = question;
				string answer = api.api_ret(requestData)["choices"][0]["message"]["content"].get<string>();
				cout << answer << '\n';
				for (int k = 0; k < 3; k++)
				{
					if (answer.find(datas[k].name) == string::npos) continue;
					if (j == 0) user.select_cpu(datas[k]);
					else if (j == 1) user.select_gpu(datas[k]);
					else if (j == 2) user.select_ram(datas[k]);
					else if (j == 3) user.select_board(datas[k]);
					else if (j == 4) user.select_storage(datas[k]);
					break;
				}
			}
			break;
		}
	}
	cout << "CPU : " << user.get_cpu_spec().name << '\n';
	cout << "GPU : " << user.get_gpu_spec().name << '\n';
	cout << "RAM : " << user.get_ram_spec().name << '\n';
	cout << "메인보드 : " << user.get_board_spec().name << '\n';
	cout << "스토리지 : " << user.get_storage_spec().name << '\n';
}
