CREATE TABLE movement (
	id BIGINT not NULL AUTO_INCREMENT,
	mtime varchar(32) NOT NULL ,
	name varchar(16) NOT NULL,
	cmd varchar(16) NOT NULL,
	PRIMARY KEY (id)
);

INSERT INTO movement (mtime, name, cmd) VALUES ('10000000','moe','forward;');
INSERT INTO movement (mtime, name, cmd) VALUES ('15001000','moe','left;');
INSERT INTO movement (mtime, name, cmd) VALUES ('20002000','moe','right;');
INSERT INTO movement (mtime, name, cmd) VALUES ('25003000','moe','backward;');
INSERT INTO movement (mtime, name, cmd) VALUES ('30004000','moe','forward;');
INSERT INTO movement (mtime, name, cmd) VALUES ('35005000','moe','forward;');
INSERT INTO movement (mtime, name, cmd) VALUES ('10000000','curly','forward;');
INSERT INTO movement (mtime, name, cmd) VALUES ('15001000','curly','left;');
INSERT INTO movement (mtime, name, cmd) VALUES ('20002000','curly','right;');
INSERT INTO movement (mtime, name, cmd) VALUES ('25003000','curly','backward;');
INSERT INTO movement (mtime, name, cmd) VALUES ('30004000','curly','forward;');
INSERT INTO movement (mtime, name, cmd) VALUES ('35005000','curly','forward;');


