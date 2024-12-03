#pragma once

namespace histogramEqualization {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Imaging;
	using namespace System::Drawing::Design;
	/// <summary>
	/// MyForm 的摘要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO:  在此加入建構函式程式碼
			//
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button_open;
	protected:

	protected:
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::PictureBox^ pictureBox2;

	protected:

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		System::ComponentModel::Container^ components;
	private: System::Windows::Forms::Button^ button_HE;
		   Bitmap^ ori_image;


#pragma region Windows Form Designer generated code
		   /// <summary>
		   /// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		   /// 這個方法的內容。
		   /// </summary>
		   void InitializeComponent(void)
		   {
			   this->button_open = (gcnew System::Windows::Forms::Button());
			   this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			   this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			   this->button_HE = (gcnew System::Windows::Forms::Button());
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			   this->SuspendLayout();
			   // 
			   // button_open
			   // 
			   this->button_open->Location = System::Drawing::Point(282, 32);
			   this->button_open->Name = L"button_open";
			   this->button_open->Size = System::Drawing::Size(75, 41);
			   this->button_open->TabIndex = 0;
			   this->button_open->Text = L"OPEN";
			   this->button_open->UseVisualStyleBackColor = true;
			   this->button_open->Click += gcnew System::EventHandler(this, &MyForm::button_open_Click);
			   // 
			   // pictureBox1
			   // 
			   this->pictureBox1->Location = System::Drawing::Point(2, 79);
			   this->pictureBox1->Name = L"pictureBox1";
			   this->pictureBox1->Size = System::Drawing::Size(640, 480);
			   this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			   this->pictureBox1->TabIndex = 1;
			   this->pictureBox1->TabStop = false;
			   // 
			   // pictureBox2
			   // 
			   this->pictureBox2->Location = System::Drawing::Point(648, 79);
			   this->pictureBox2->Name = L"pictureBox2";
			   this->pictureBox2->Size = System::Drawing::Size(640, 480);
			   this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			   this->pictureBox2->TabIndex = 2;
			   this->pictureBox2->TabStop = false;
			   // 
			   // button_HE
			   // 
			   this->button_HE->Location = System::Drawing::Point(928, 32);
			   this->button_HE->Name = L"button_HE";
			   this->button_HE->Size = System::Drawing::Size(75, 41);
			   this->button_HE->TabIndex = 0;
			   this->button_HE->Text = L"HE";
			   this->button_HE->UseVisualStyleBackColor = true;
			   this->button_HE->Click += gcnew System::EventHandler(this, &MyForm::button_HE_Click);
			   // 
			   // MyForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->AutoSize = true;
			   this->ClientSize = System::Drawing::Size(1310, 634);
			   this->Controls->Add(this->pictureBox2);
			   this->Controls->Add(this->pictureBox1);
			   this->Controls->Add(this->button_HE);
			   this->Controls->Add(this->button_open);
			   this->Name = L"MyForm";
			   this->Text = L"MyForm";
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
#pragma endregion
	private: System::Void button_open_Click(System::Object^ sender, System::EventArgs^ e) {
		//open file on pictureBox1
		//new一個新的openFileDialog1開啟檔案
		//開啟檔案對話窗 記得「^」
		OpenFileDialog^ ofd = gcnew OpenFileDialog();
		//預設檔案名稱為空值
		ofd->FileName = "";
		//設定Filter，用以限定使用者開啟的檔案
		ofd->Filter = "ALL Files(*.*)|*.*";
		// 設定Filter選擇模式(依照Filter數，如本例選擇1表示起始出現的為點陣圖，選擇2表示All filts)
		ofd->FilterIndex = 1;
		//跳出檔案選擇視窗(ShowDialog)，並且如果使用者點選檔案，並且檔案名稱超過0個字元，則判斷是為True，進入處理程序
		if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK && ofd->FileName != "") {
			//將選取的檔案讀取並且存至ori_image
			ori_image = gcnew Bitmap(ofd->FileName);
			//將影像顯示在pictureBox1
			pictureBox1->Image = ori_image;
		}
	}
	private: System::Void button_HE_Click(System::Object^ sender, System::EventArgs^ e) {
		//if not open photo leave this process
		if (ori_image == nullptr) {
			return;
		}
		//建立輸出點陣圖
		Bitmap^ output = gcnew Bitmap(ori_image->Width, ori_image->Height, ori_image->PixelFormat);
		//BitmapData 需要加入namespace
		//lock Memory to edit it
		//在Memory建立靜態位址空間，讓該部分Memory空間不被占用
		BitmapData^ bd_ori = ori_image->LockBits(Rectangle(0, 0, ori_image->Width, ori_image->Height), ImageLockMode::ReadWrite, ori_image->PixelFormat);
		BitmapData^ bd_output = output->LockBits(Rectangle(0, 0, output->Width, output->Height), ImageLockMode::ReadWrite, output->PixelFormat);

		//因為BitmapData 提供像素指標和可能會產生一些不需要的圖片
		int ori_byteskip = bd_ori->Stride - bd_ori->Width * 3;
		int output_byteskip = bd_output->Stride - bd_output->Width * 3;

		//set pointer to start
		//設定影像初始指標位址，也就是影像的第一個像素
		Byte* ori_ptr = (Byte*)((void*)bd_ori->Scan0);
		Byte* output_ptr = (Byte*)((void*)bd_output->Scan0);
		int grayForm[256] = {};
		int grayFormN[256] = {};
		int sMin = 100;
		int sMax = 180;
		int rMin = 0;
		int rMax = 0;
		int counterMax = 0;

		//灰階演算法  
		for (int y = 0; y < bd_ori->Height; y++) {
			for (int x = 0; x < bd_ori->Width; x++) {
				//像素值填入
				int B = (int)ori_ptr[0];
				int G = (int)ori_ptr[1];
				int R = (int)ori_ptr[2];
				int gray = (R + G + B) / 3;
				grayForm[gray]++;

				// 跳到下個像素
				ori_ptr += 3;
			}
			ori_ptr += ori_byteskip;
		}
		//clip 3%
		/*for (int i = 0; i < 256; i++) {
			if (counterMax < grayForm[i]) {
				counterMax = grayForm[i];
			}
		}
		counterMax = counterMax * 0.03;
		for (int i = 0; i < 256; i++) {
			if ((grayForm[i] - counterMax) < 0) {
				grayForm[i] = 0;
			}
			else {
				grayForm[i] -= counterMax;
			}
		}*/
		for (int i = 0; i < 256; i++) {
			if (rMin == 0 && grayForm[i] != 0) {
				rMin = i;
			}
			if (grayForm[i] != 0) {
				rMax = i;
			}
		}
		ori_ptr = (Byte*)((void*)bd_ori->Scan0);
		output_ptr = (Byte*)((void*)bd_output->Scan0);
		int newGray = 0;
		float scale = (float)(sMax - sMin) / (rMax - rMin);
		for (int y = 0; y < bd_ori->Height; y++) {
			for (int x = 0; x < bd_ori->Width; x++) {
				//像素值填入
				int B = (int)ori_ptr[0];
				int G = (int)ori_ptr[1];
				int R = (int)ori_ptr[2];
				int gray = (R + G + B) / 3;

				newGray = (scale * gray) - (scale * rMin) + sMin;

				//newGray = gray;
				if (newGray > 255) {
					newGray = 255;
				}
				else if (newGray < 0) {
					newGray = 0;
				}
				grayFormN[newGray]++;
				output_ptr[0] = newGray;
				output_ptr[1] = newGray;
				output_ptr[2] = newGray;

				// 跳到下個像素

				ori_ptr += 3;
				output_ptr += 3;

			}
			//throw garbage
			ori_ptr += ori_byteskip;
			output_ptr += output_byteskip;
		}
		grayForm[0]++;
		grayFormN[0]++;
		//Unlock處理完畢的像素範圍
		ori_image->UnlockBits(bd_ori);
		output->UnlockBits(bd_output);
		//將影像顯示在pictureBox2
		pictureBox2->Image = output;
	}
	};
}
