#pragma once

char HexChar(char c)
{
	if ((c >= '0') && (c <= '9'))
		return c - 0x30;
	else if ((c >= 'A') && (c <= 'F'))
		return c - 'A' + 10;
	else if ((c >= 'a') && (c <= 'f'))
		return c - 'a' + 10;
	else
		return 0x10;
}

int Str2Hex(CString str, CByteArray &data)
{
	int t, t1;
	int rlen = 0, len = str.GetLength();
	data.SetSize(len / 2);
	for (int i = 0; i < len;)
	{
		char l, h = str[i];
		if (h == ' ')
		{
			i++;
			continue;
		}
		i++;
		if (i >= len)
			break;
		l = str[i];
		t = HexChar(h);
		t1 = HexChar(l);
		if ((t == 16) || (t1 == 16))
			break;
		else
			t = t * 16 + t1;
		i++;
		data[rlen] = (char)t;
		rlen++;
	}
	data.SetSize(rlen);
	return rlen;
}



int bcd_ToUInt(unsigned char *buffer)
{
	unsigned long rslt = 0;

	if (buffer[0] == 0x02)
	{
		int len = 0;
		for (unsigned int i = 3; i < 255 + 3; ++i, ++len)
		{
			if (buffer[i] == 0x03)
				return len;
		}
	}
	return -1;
}

void GetData(unsigned char *in, CString &out)
{
	int len = bcd_ToUInt(in);
	out = "";
	char *str = out.GetBuffer();
	for (int i = 0; i < len; ++i)
	{
		out.Append((CString)&in[i + 3], 1);
	}
}


unsigned char LRCBuffer(void *buffer)
{
	int len = bcd_ToUInt((unsigned char*)buffer);
	unsigned char *lrcBuf = (unsigned char*)buffer;
	len += 2 + 1;
	lrcBuf = &lrcBuf[1];
	printf("LRC Before:");
	for (int i = 0; i < len; ++i)
	{
		printf("%02x ", lrcBuf[i]);
	}
	printf("\n");
	unsigned char nOr = 0;
	nOr = lrcBuf[0];
	for (int i = 0; i < len - 1; ++i)
	{
		nOr ^= lrcBuf[i + 1];
	}
	printf("LRC After:%02x\n", nOr);
	return nOr;
}

int DectoBCD(int Dec, unsigned char *Bcd, int length)
{
	int i;
	int temp;

	for (i = length - 1; i >= 0; i--)
	{
		temp = Dec % 100;
		Bcd[i] = static_cast<unsigned char>(((temp / 10) << 4) + ((temp % 10) & 0x0F));
		Dec /= 100;
	}

	return 0;
}