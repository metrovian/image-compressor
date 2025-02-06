#include "HUFF.h"
#include "HeaderHUFF.h"

bool HUFF::node::operator>(const node& _node)
{
    return this->freq > _node.freq;
}

bool HUFF::node::operator<(const node& _node)
{
    return this->freq < _node.freq;
}

bool HUFF::less(node* _node, node* _mode)
{
    return *_node < *_mode;
}

bool HUFF::greater(node* _node, node* _mode)
{
    return *_node > *_mode;
}

bool HUFF::free(node* _node)
{
    if (!_node) return false;

    free(_node->left);
    free(_node->right);

    delete _node;

    return true;
}

bool HUFF::match(node* _node, std::vector<bool> _code)
{
    if (!_node) return false;

    if (!_node->left && !_node->right) 
    {
        code[_node->pval] = _code;
    }

    std::vector<bool> lcd = _code;
    std::vector<bool> rcd = _code;

    lcd.push_back(0);
    rcd.push_back(1);

    match(_node->left, lcd);
    match(_node->right, rcd);

    return true;
}

bool HUFF::decode(const std::string& _fname)
{
    return false;
}

bool HUFF::encode(const std::string& _fname)
{
    if (data.empty()) return false;

    std::unordered_map<uint8_t, uint64_t> map;
    std::priority_queue<node*, std::vector<node*>, decltype(&HUFF::greater)> heap(&HUFF::greater);
    
    for (uint64_t i = 0; i < data.size(); ++i)
    {
        ++map[data[i]];
    }

    for (const auto& pair : map)
    {
        heap.push(new node(pair.first, pair.second));
    }

    while (heap.size() > 1)
    {
        node* left = heap.top(); 
        heap.pop();

        node* right = heap.top();
        heap.pop();

        node* parent = new node(0, left->freq + right->freq);

        parent->left = left;
        parent->right = right;

        heap.push(parent);
    }

    node* root = heap.top();
    heap.pop();

    match(root, std::vector<bool>());
    free(root);

    std::vector<bool> cbts;

    for (uint64_t i = 0; i < data.size(); ++i)
    {
        cbts.insert(cbts.end(), code[data[i]].begin(), code[data[i]].end());
    }

    uint8_t byte = 0x00;
    uint8_t count = 0x00;

    comp.clear();

    for (uint64_t i = 0; i < cbts.size(); ++i)
    {
        byte = cbts[i] + (byte << 1);
        ++count;

        if (count == 0x08)
        {
            comp.push_back(byte);

            byte = 0x00;
            count = 0x00;
        }
    }

    if (count > 0)
    {
        byte <<= (0x08 - count);
        comp.push_back(byte);
    }

    HeaderHUFF header;
    std::ofstream ofs(_fname, std::ios::binary);

    if (!ofs.is_open())
    {
        std::cerr << "Open Error : " << _fname << std::endl;
        return false;
    }

    header.width = width;
    header.height = height;

    header.fsi = comp.size() + header.ofs;
    header.dsi = comp.size();

    ofs.write(reinterpret_cast<const char*>(&header), header.ofs);
    ofs.write(reinterpret_cast<const char*>(comp.data()), header.dsi);

    for (const auto& pair : map)
    {
        ofs << pair.first << pair.second;
    }

    ofs.close();

    return comp.size() < data.size();
}