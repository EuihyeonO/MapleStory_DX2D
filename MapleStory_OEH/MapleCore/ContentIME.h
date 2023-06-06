#pragma once

class ContentIME
{

public:

	ContentIME();
	~ContentIME();

	ContentIME(const ContentIME& _Other) = delete;
	ContentIME(ContentIME&& _Other) noexcept = delete;
	ContentIME& operator=(const ContentIME& _Other) = delete;
	ContentIME& operator=(ContentIME&& _Other) noexcept = delete;

protected:

private:

	void InitIME();

};

