#ifndef LAB11_BIN_MANIP_H_INCLUDED
#define LAB11_BIN_MANIP_H_INCLUDED

#pragma once
#include <iostream>
#include <cstdint>
#include <cstddef>

struct write_le_int32 {
    write_le_int32(std::int32_t _data) : data(_data) {}
    friend std::ofstream& operator<<(std::ofstream&, const write_le_int32&);
private:
    std::int32_t data;
};

struct read_le_int32 {
    read_le_int32(std::int32_t& _data) : data(_data) {}
    friend std::ifstream& operator>>(std::ifstream&, const read_le_int32&);
private:
    std::int32_t& data;
};

struct write_bool {
    write_bool(bool _data) : data(_data) {}
    friend std::ofstream& operator<<(std::ofstream&, const write_bool&);
private:
    bool data;
};

struct read_bool{
    read_bool(bool& _data) : data(_data) {}
    friend std::ifstream& operator>>(std::ifstream&, const read_bool&);
private:
    bool& data;
};

struct write_c_str {
    write_c_str(const char* _data) : data(_data) {}
    friend std::ofstream& operator<<(std::ofstream&, const write_c_str&);
private:
    const char* data;
};

struct read_c_str {
    read_c_str(char* _data, std::size_t _size) : data(_data), size(_size) {}
    friend std::ifstream& operator>>(std::ifstream&, const read_c_str&);
private:
    char* data;
    std::size_t size;
};

#endif

