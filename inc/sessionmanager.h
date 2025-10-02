#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include <QString>

class SessionManager {
public:
    static SessionManager& instance() {
        static SessionManager instance;
        return instance;
    }

    void setSession(const QString &user, const QString &token) {
        username = user;
        sessionToken = token;
    }

    void clearSession() {
        username.clear();
        sessionToken.clear();
    }

    QString getUsername() const { return username; }
    QString getSessionToken() const { return sessionToken; }

private:
    SessionManager() {}  // Private constructor to prevent direct instantiation
    SessionManager(const SessionManager&) = delete;
    SessionManager& operator=(const SessionManager&) = delete;

    QString username;
    QString sessionToken;
};

#endif // SESSIONMANAGER_H
