#pragma once
#include<iostream>
#include<stdlib.h>
#include<vector>
#include<sstream>
#include<stdint.h>
#include<boost/filesystem.hpp>
#include<fstream>
#ifdef _WIN32
#include <WinSock2.h> //�׽��ֵ�ͷ�ļ�
#include <WS2tcpip.h>
#include <Iphlpapi.h>//��ȡ������Ϣ�ӿڵ�ͷ�ļ�
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "Iphlpapi.lib")//��ȡ������Ϣ�ӿڵĿ��ļ�����

#else 
#endif

class StringUtil
{
public:
	static int Str2Dig(const std::string &num)
	{
		std::stringstream tmp;
		tmp << num;
		int res;
		tmp >> res;
		return res;
	}
};

class FileUtil
{
public:
	static uint64_t GetFilesize(const std::string &name)
	{
		return boost::filesystem::file_size(name);
	}

	static bool Write(const std::string &name, const std::string &body, int offset = 0)
	{
		FILE *fp = NULL;
		fopen_s(&fp, name.c_str(), "wb+");
		if (fp == NULL)
		{
			std::cerr << "���ļ�ʧ��\n";
			return false;
		}
		fseek(fp, offset, SEEK_SET);
		size_t ret = fwrite(body.c_str(), 1, body.size(), fp);
		if (ret != body.size())
		{
			std::cerr << "���ļ�д������ʧ��\n";
			fclose(fp);
			return false;
		}
		fclose(fp);
		return true;
	}

	//ָ�������ʾ����һ������Ͳ���
	//const & ��ʾ����һ�������Ͳ���
	//&��ʾ����һ������һ����������Ͳ���
	static bool Read(const std::string &name, std::string *body)
	{
		uint64_t filesize = boost::filesystem::file_size(name);
		body->resize(filesize);
		std::cout << "��ȡ�ļ�����:" << name << "size:" << filesize << "\n";
		FILE *fp = NULL;
		fopen_s(&fp, name.c_str(), "rb+");
		if (fp == NULL)
		{
			std::cerr << "���ļ�����ʧ��\n";
			return false;
		}
		size_t ret = fread(&(*body)[0], 1, filesize, fp);
		if (ret != filesize)
		{
			std::cerr << "��ȡ�ļ�ʧ��\n";
			fclose(fp);
			return false;
		}
		fclose(fp);
		return true;
	}

	static bool ReadRange(const std::string &name, std::string  *body, int len, int offset)
	{
		body->resize(len);
		FILE *fp = NULL;
		fopen_s(&fp, name.c_str(), "rb+");
		if (fp == NULL)
		{
			std::cerr << "���ļ�����ʧ��\n";
			return false;
		}
		fseek(fp, offset, SEEK_SET);
		size_t ret = fread(&(*body)[0], 1, len, fp);
		if (ret != len)
		{
			std::cerr << "��ȡ�ļ�ʧ��\n";
			fclose(fp);
			return false;
		}
		fclose(fp);
		return true;
	}

	//��ȡ�ֿ�����
	static bool GetRange(const std::string& range_str, int* start, int* end)
	{
		size_t  pos1 = range_str.find('-');
		size_t pos2 = range_str.find('=');
		*start = std::atol(range_str.substr(pos2 + 1, pos1 - pos2 - 1).c_str());
		std::cout << "range_str.substr(pos1 + 1, pos1 - pos2 - 1):" << range_str.substr(pos1 + 1, pos1 - pos2 - 1) << std::endl;
		*end = std::atol(range_str.substr(pos1 + 1).c_str());
		std::cout << "range_str.substr(pos1 + 1):" << range_str.substr(pos1 + 1) << std::endl;
		return true;
	}
};

class Adapter
{
public:
	uint32_t _ip_addr;
	uint32_t _mask_addr;
};

class AdapterUtil
{
public:
#ifdef _WIN32
	//windows�»�ȡ������Ϣʵ��
	static bool  GetAllAdapter(std::vector<Adapter> *list)
	{
		PIP_ADAPTER_INFO p_adapters = new IP_ADAPTER_INFO();
		//GetAdaptersInfo  windows�»�ȡ������Ϣ�ӿ���Ϣ--������Ϣ�����ж��--��˴���һ��ָ��
		//��ȡ������Ϣ�п���ʧ��
		//��Ϊ�ռ䲻�㣬�����һ������Ͳ������������û���������������Ϣ�ռ����õ��Ĵ�С

		uint64_t  all_adapter_size = sizeof(PIP_ADAPTER_INFO);
		int ret = GetAdaptersInfo(p_adapters, (PULONG)&all_adapter_size);

		if (ret == ERROR_BUFFER_OVERFLOW)//��������ʾ�������ռ䲻��
		{
			delete p_adapters;
			p_adapters = (PIP_ADAPTER_INFO)new BYTE[all_adapter_size];
			GetAdaptersInfo(p_adapters, (PULONG)&all_adapter_size);//���»�ȡ������Ϣ
		}

		while (p_adapters)
		{
			Adapter adapter;
			inet_pton(AF_INET, p_adapters->IpAddressList.IpAddress.String, &adapter._ip_addr);
			inet_pton(AF_INET, p_adapters->IpAddressList.IpMask.String, &adapter._mask_addr);
			if (adapter._ip_addr != 0) //��ΪĳЩ������û�����ã�����ip��ַΪ0
			{
				list->push_back(adapter); //��������Ϣ��ӵ�vector�з��ظ��û�
			}
			p_adapters = p_adapters->Next;
		}
		delete p_adapters;
		return true;
	}

#else
	//Linux�»�ȡ������Ϣʵ��
	bool GetAllAdapter(std::vector<Adapter> *list);
	{
		return true;
	}
#endif
};