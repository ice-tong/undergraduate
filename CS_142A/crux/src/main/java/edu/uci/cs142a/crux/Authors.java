package edu.uci.cs142a.crux;

final class Authors {
    // TODO: Add author information.
    static final Author[] all = {
            new Author("Kian Farsany", "55375951", "kfarsany"),
    };
}

final class Author {
    final String name;
    final String studentId;
    final String uciNetId;

    Author(String name, String studentId, String uciNetId) {
        this.name = name;
        this.studentId = studentId;
        this.uciNetId = uciNetId;
    }
}
