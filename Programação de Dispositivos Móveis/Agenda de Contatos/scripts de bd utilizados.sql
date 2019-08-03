//Tabela de contatos, if a tabela não existir ele cria a tabela, o id tem sempre que ser assim _d a plaaforma android define isso

CREATE TABLE IF NOT EXISTS CONTATO(
        _id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
        TELEFONE VARCHAR(14).
        TIPOTELEFONE VARCHAR(1),
        EMAIL VARCHAR(255),
        TIPOEMAIL VARCHAR(1),
        ENDERECO VARCHAR(255),
        TIPOENDERECO VARCHAR(1),
        DATASESPECIAIS DATE,
        TIPOSDATASESPECIAIS VARCHAR(1),
        GRUPOS VARCHAR(255)
);