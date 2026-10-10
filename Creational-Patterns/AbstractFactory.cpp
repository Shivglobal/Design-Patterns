#include <iostream>
#include <memory>

class IDBConnection {
public:
    virtual void connect() = 0;
    virtual ~IDBConnection() = default;
};

class IDBCommand {
public:
    virtual void execute() = 0;
    virtual ~IDBCommand() = default;
};

class OracleConnection : public IDBConnection {
public:
    void connect() override {
        std::cout << "Connected to Oracle\n";
    }
};

class OracleCommand : public IDBCommand {
public:
    void execute() override {
        std::cout << "Executing Oracle SQL\n";
    }
};

class PostgreSQLConnection : public IDBConnection {
public:
    void connect() override {
        std::cout << "Connected to PostgreSQL\n";
    }
};

class PostgreSQLCommand : public IDBCommand {
public:
    void execute() override {
        std::cout << "Executing PostgreSQL SQL\n";
    }
};

class MongoConnection : public IDBConnection {
public:
    void connect() override {
        std::cout << "Connected to MongoDB\n";
    }
};

class MongoCommand : public IDBCommand {
public:
    void execute() override {
        std::cout << "Executing Mongo Query\n";
    }
};
class IDBFactory {
public:
    virtual std::unique_ptr<IDBConnection> createConnection() = 0;
    virtual std::unique_ptr<IDBCommand> createCommand() = 0;

    virtual ~IDBFactory() = default;
};
class OracleFactory : public IDBFactory {
public:
    std::unique_ptr<IDBConnection> createConnection() override {
        return std::make_unique<OracleConnection>();
    }

    std::unique_ptr<IDBCommand> createCommand() override {
        return std::make_unique<OracleCommand>();
    }
};
class PostgreSQLFactory : public IDBFactory {
public:
    std::unique_ptr<IDBConnection> createConnection() override {
        return std::make_unique<PostgreSQLConnection>();
    }

    std::unique_ptr<IDBCommand> createCommand() override {
        return std::make_unique<PostgreSQLCommand>();
    }
};
class MongoFactory : public IDBFactory {
public:
    std::unique_ptr<IDBConnection> createConnection() override {
        return std::make_unique<MongoConnection>();
    }

    std::unique_ptr<IDBCommand> createCommand() override {
        return std::make_unique<MongoCommand>();
    }
};
void runDatabase(IDBFactory& factory)
{
    auto conn = factory.createConnection();
    auto cmd  = factory.createCommand();

    conn->connect();
    cmd->execute();
}

int main()
{
    OracleFactory oracle;
    runDatabase(oracle);

    PostgreSQLFactory postgres;
    runDatabase(postgres);

    MongoFactory mongo;
    runDatabase(mongo);
}

