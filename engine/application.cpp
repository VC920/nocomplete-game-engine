#include "application.h"

void Application::SetShouldClosed(bool value)
{
    m_shouldClosed = value;
}

bool Application::ShouldClosed() const
{
    return m_shouldClosed;
}
