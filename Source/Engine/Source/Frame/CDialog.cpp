#include "CDialog.h"

// Reverse engineered from Warcraft III binary

CDialog::CDialog() : m_modal(false), m_result(0) {}
CDialog::~CDialog() {}

const char* CDialog::GetTitle() const { return m_title.c_str(); }
void CDialog::SetTitle(const char* title) { m_title = title ? title : ""; }

bool CDialog::IsModal() const { return m_modal; }
void CDialog::SetModal(bool modal) { m_modal = modal; }

void CDialog::Show() { SetVisible(true); }
void CDialog::Hide() { SetVisible(false); }
void CDialog::Close() { SetVisible(false); }

int32_t CDialog::GetResult() const { return m_result; }
void CDialog::SetResult(int32_t result) { m_result = result; }
