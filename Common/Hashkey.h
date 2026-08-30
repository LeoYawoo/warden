#pragma once

class HASHKEY_4CC {
public:
protected:
    char m_key[4];
};

class HASHKEY_CONSTSTR {
public:
protected:
    const char *m_key;
};

class HASHKEY_DWORD {
public:
protected:
    unsigned int m_key;
};


class HASHKEY_PTR {
public:
    // Member variables
    void *m_key;

    // Member functions
    bool operator==(const HASHKEY_PTR &key);
};

class HASHKEY_STR {
public:
    // Member variables
    char *m_str = nullptr;

    // Member functions
    HASHKEY_STR() : m_str(nullptr) {}

    ~HASHKEY_STR();

    HASHKEY_STR &operator=(const char *str);

    bool operator==(const char *str);

    const char *GetStr() const { return m_str; }
};

class HASHKEY_STRI : public HASHKEY_STR {
public:
    // Member functions
    HASHKEY_STRI &operator=(const char *str);

    bool operator==(const char *str);

};

class HASHKEY_STRI_P {
public:
    HASHKEY_STRI_P();

    bool operator==(const HASHKEY_STRI_P &key);

protected:
    void *m_key;
};

class HASHKEY_NONE {
public:
    // Member functions
    bool operator==(const HASHKEY_NONE &key);
};

class HASHKEY_STRIPACKED : public HASHKEY_STRI {
public:
    HASHKEY_STRIPACKED();

    HASHKEY_STRIPACKED(const char *a2);
};

