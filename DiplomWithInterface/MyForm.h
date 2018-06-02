#pragma comment(lib, "WS2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define DEFAULT_BUFLEN 1024
#include <stdio.h>
#include <winsock2.h>
#include <msclr\marshal_cppstd.h>
#include <iostream>

#pragma once

namespace DiplomWithInterface {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Runtime::InteropServices;

	/// <summary>
	/// —водка дл€ MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}
		array<String ^>^ rgbNames;
	private: System::Windows::Forms::Label^  label4;
	public:
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label5;
			 array<String ^> ^depthNames;
	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected:
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::OpenFileDialog^  openFile;


	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->openFile = (gcnew System::Windows::Forms::OpenFileDialog());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(0, 22);
			this->label1->TabIndex = 2;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->ForeColor = System::Drawing::Color::Teal;
			this->label3->Location = System::Drawing::Point(27, 53);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(90, 19);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Depth frames";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->ForeColor = System::Drawing::Color::Teal;
			this->label2->Location = System::Drawing::Point(27, 19);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(84, 19);
			this->label2->TabIndex = 4;
			this->label2->Text = L"RGB frames";
			// 
			// button1
			// 
			this->button1->CausesValidation = false;
			this->button1->Cursor = System::Windows::Forms::Cursors::Default;
			this->button1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->ForeColor = System::Drawing::Color::DarkSlateGray;
			this->button1->Location = System::Drawing::Point(166, 16);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(119, 27);
			this->button1->TabIndex = 6;
			this->button1->Text = L"Open RGB frames";
			this->button1->UseCompatibleTextRendering = true;
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button2->ForeColor = System::Drawing::Color::DarkSlateGray;
			this->button2->Location = System::Drawing::Point(166, 50);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(119, 27);
			this->button2->TabIndex = 7;
			this->button2->Text = L"Open depth frames";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button3->ForeColor = System::Drawing::Color::DarkSlateGray;
			this->button3->Location = System::Drawing::Point(31, 89);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(254, 24);
			this->button3->TabIndex = 8;
			this->button3->Text = L"Combine";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// openFile
			// 
			this->openFile->FileName = L"openFile";
			this->openFile->Multiselect = true;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->ForeColor = System::Drawing::Color::Teal;
			this->label4->Location = System::Drawing::Point(9, 11);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(323, 19);
			this->label4->TabIndex = 9;
			this->label4->Text = L"Select RGB frames and corresponding depth frames";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->button3);
			this->groupBox1->Controls->Add(this->button1);
			this->groupBox1->Controls->Add(this->button2);
			this->groupBox1->Location = System::Drawing::Point(12, 34);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(320, 119);
			this->groupBox1->TabIndex = 10;
			this->groupBox1->TabStop = false;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->textBox2);
			this->groupBox2->Controls->Add(this->textBox1);
			this->groupBox2->Controls->Add(this->label7);
			this->groupBox2->Controls->Add(this->label6);
			this->groupBox2->Location = System::Drawing::Point(13, 182);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(318, 82);
			this->groupBox2->TabIndex = 11;
			this->groupBox2->TabStop = false;
			// 
			// textBox2
			// 
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox2->ForeColor = System::Drawing::Color::DarkSlateGray;
			this->textBox2->Location = System::Drawing::Point(172, 49);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(112, 22);
			this->textBox2->TabIndex = 12;
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox1->ForeColor = System::Drawing::Color::DarkSlateGray;
			this->textBox1->Location = System::Drawing::Point(172, 16);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(112, 22);
			this->textBox1->TabIndex = 11;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label7->ForeColor = System::Drawing::Color::Teal;
			this->label7->Location = System::Drawing::Point(26, 49);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(99, 19);
			this->label7->TabIndex = 10;
			this->label7->Text = L"Matching error";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label6->ForeColor = System::Drawing::Color::Teal;
			this->label6->Location = System::Drawing::Point(26, 16);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(97, 19);
			this->label6->TabIndex = 9;
			this->label6->Text = L"Execution time";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->ForeColor = System::Drawing::Color::Teal;
			this->label5->Location = System::Drawing::Point(128, 159);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(81, 19);
			this->label5->TabIndex = 12;
			this->label5->Text = L"Output data";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(343, 275);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label1);
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Text = L"Combining of 3D point clouds";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e)
	{
		Stream^ myStream;
		openFile->InitialDirectory = "C:";
		openFile->Filter = "png files (*.png)|*.png";
		openFile->FilterIndex = 2;
		if (openFile->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			if ((myStream = openFile->OpenFile()) != nullptr)
			{
				// Insert code to read the stream here.
				rgbNames = openFile->FileNames;
				myStream->Close();
			}
		}
	}
	
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		Stream^ myStream;
		openFile->InitialDirectory = "C:";
		openFile->Filter = "png files (*.png)|*.png";
		openFile->FilterIndex = 2;
		if (openFile->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			if ((myStream = openFile->OpenFile()) != nullptr)
			{
				// Insert code to read the stream here.
				depthNames = openFile->FileNames;
				myStream->Close();
			}
		}
	}
	
	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		std::vector<std::string> digits1, digits2;
		for (int i = 0; i < rgbNames->Length; i++) 
		{
			const char* ptr1 = (const char*)(Marshal::StringToHGlobalAnsi(rgbNames[i])).ToPointer();
			std::string str1 = "";
			for (int j = 0; j < rgbNames[i]->Length; j++) 
			{
				if (isdigit(ptr1[j])) 
				{
					str1 += ptr1[j];
				}
			}	
			digits1.push_back(str1);
		}

		for (int i = 0; i < depthNames->Length; i++)
		{
			const char* ptr2 = (const char*)(Marshal::StringToHGlobalAnsi(depthNames[i])).ToPointer();
			std::string str1 = "";
			for (int j = 0; j < depthNames[i]->Length; j++)
			{
				if (isdigit(ptr2[j]))
				{
					str1 += ptr2[j];
				}
			}
			digits2.push_back(str1);
		}
		
		bool exit = false;
		for (int i = 0; i < digits1.size(); i++)
		{
			if (strcmp(digits1[i].c_str(), digits2[i].c_str()) != 0) 
			{
				MessageBox::Show("RGB frame and corresponding depth frame aren't equal!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				exit = true;
			}
		}

		if (exit == 0) 
		{
			if (rgbNames->Length != depthNames->Length)
			{
				MessageBox::Show("Number of rgb and depth frames should be equal!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
			else
			{
				int count = rgbNames->Length;
				std::string names = "";
				for (int i = 0; i < count; i++)
				{
					const char* ptr1 = (const char*)(Marshal::StringToHGlobalAnsi(rgbNames[i])).ToPointer();
					names = names + ptr1 + " ";
					const char* ptr2 = (const char*)(Marshal::StringToHGlobalAnsi(depthNames[i])).ToPointer();
					names = names + ptr2 + " ";
				}

				WORD ver = MAKEWORD(2, 2);
				WSADATA wsaData;
				int retVal = 0;

				WSAStartup(ver, (LPWSADATA)& wsaData);

				LPHOSTENT hostEnt;
				hostEnt = gethostbyname("localhost");

				//—оздаем сокет
				SOCKET clientSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
				SOCKADDR_IN serverInfo;

				serverInfo.sin_family = PF_INET;
				serverInfo.sin_addr = *((LPIN_ADDR)*hostEnt->h_addr_list);
				serverInfo.sin_port = htons(1111);

				retVal = connect(clientSock, (LPSOCKADDR)& serverInfo, sizeof(serverInfo));

				const char *pBuf = names.c_str();
				int  size = strlen(pBuf);
				retVal = send(clientSock, pBuf, size, 0);

				char szResponse[DEFAULT_BUFLEN];
				retVal = recv(clientSock, szResponse, DEFAULT_BUFLEN, 0);

				std::vector<std::string> response;
				std::string delim(" ");
				size_t prev = 0;
				size_t next;
				size_t delta = delim.length();
				std::string str(szResponse);

				while ((next = str.find(delim, prev)) != std::string::npos) {
					std::string tmp = str.substr(prev, next - prev);
					response.push_back(str.substr(prev, next - prev));
					prev = next + delta;
				}
				textBox1->Text = gcnew String((response[0] + " seconds").c_str());
				textBox2->Text = gcnew String(response[1].c_str());
				closesocket(clientSock);
				WSACleanup();
			}
		}
	}
};
}
