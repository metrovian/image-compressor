#pragma once
#include "BMP.h"

class HUFF : public BMP
{
protected: /* struct */
	struct node
	{
		uint8_t pval = 0;
		uint64_t freq = 0;
		node* left = NULL;
		node* right = NULL;

		bool operator>(const node& _node);
		bool operator<(const node& _node);

		node(uint8_t _pval, uint64_t _freq) : pval(_pval), freq(_freq) {};
	};

protected: /* data */
	std::vector<uint8_t> comp;
	std::unordered_map<uint8_t, std::vector<bool>> code;

protected: /* condition */
	static bool less(node* _node, node* _mode);
	static bool greater(node* _node, node* _mode);

protected: /* recursive */
	bool free(node* _node);
	bool match(node* _node, std::vector<bool> _code);

public: /* compression */
	virtual bool decode(const std::string& _fname);
	virtual bool encode(const std::string& _fname);
};