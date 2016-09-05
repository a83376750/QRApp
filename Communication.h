#pragma once
#define INI_COMDEF "COMDEF"

class Communication
{
public:
	Communication();
	virtual ~Communication();

	virtual bool Open() = 0;
	virtual void Close() = 0;
	virtual bool Write(void *buffer, size_t len) = 0;
	virtual DWORD Read(void *buffer, size_t len) = 0;
};

class ComConnect : public Communication
{
public:
	ComConnect();
	~ComConnect();
	void InitConfig();
	bool CheckInvalid();
	virtual bool Open() override;
	virtual void Close() override;
	virtual bool Write(void *buffer, size_t len) override;
	virtual DWORD Read(void *buffer, size_t len) override;
private:
	HANDLE hCom;
};