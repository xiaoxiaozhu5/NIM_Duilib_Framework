#include "stdafx.h"
#include "basic_form.h"

#include <fstream>
#include <iomanip>
#include <sstream>

#pragma comment(lib, "Bcrypt.lib")

const std::wstring BasicForm::kClassName = L"Basic";

BasicForm::BasicForm()
{
}


BasicForm::~BasicForm()
{
}

std::wstring BasicForm::GetSkinFolder()
{
	return L"basic";
}

std::wstring BasicForm::GetSkinFile()
{
	return L"basic.xml";
}

std::wstring BasicForm::GetWindowClassName() const
{
	return kClassName;
}

void BasicForm::InitWindow()
{
	label_ = (ui::Label*)FindControl(L"tooltip");

	std::string sCrt("test.png");
	std::ifstream in(sCrt.c_str(), std::ios::in | std::ios::binary);
	std::string file_content((std::istreambuf_iterator<char>(in)), 
	std::istreambuf_iterator<char>());
	in.close();

	image_data_ = file_content;

	if(image_data_.empty()) {
		label_->SetText(L"read file error");
		return;
	}

	unsigned char hash[MAX_PATH] = {0};
	unsigned int hash_len = MAX_PATH;
	auto rc = nbase::hash((PBYTE)image_data_.data(), image_data_.size(), hash, &hash_len);
	if(!rc) {
		label_->SetText(L"hash failed");
		return;
	}

	std::ostringstream buffer;
     for (int i = 0; i < hash_len; ++i) {
       buffer << std::hex
              << std::setw(2)
              << std::setfill('0')
              << static_cast<int>( hash[i] );
     }

	std::wstring imageFullPath;
	ui::StringHelper::MBCSToUnicode(buffer.str(), imageFullPath);

	label_->SetBkImage(imageFullPath, (unsigned char*)image_data_.data(), image_data_.size());
}

LRESULT BasicForm::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	PostQuitMessage(0L);
	return __super::OnClose(uMsg, wParam, lParam, bHandled);
}
