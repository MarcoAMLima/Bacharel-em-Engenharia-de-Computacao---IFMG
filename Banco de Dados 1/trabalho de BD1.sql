
/*criação do banco de dados*/
create database Clinica;

/*comando para colocar banco em uso*/
use Clinica;

/*Criação das tabelas*/
create table clinica(cnpj_cli int not null, nom_cli varchar(50), primary key(cnpj_cli));
create table paciente(cpf_pac int not null, nom_pac varchar(50), dat_nas date, tel_pac varchar(20), primary key(cpf_pac));
create table quarto(num_qua int not null, num_and int, primary key(num_qua));
create table formacao(dat_for date, nom_fac varchar(30));
create table especialidade(cod_esp int not null,dsc_esp varchar(50), primary key(cod_esp));
create table medico(crm_med int not null, nom_med varchar(50), dat_nas date, val_sal decimal(15,2), primary key(crm_med));
create table tratamento(dat_ini date not null, date_fin date, val_tot decimal(15,2), primary key(dat_ini));

/*adicionando as chaves estrangeiras*/
alter table paciente add crm_med int;
alter table paciente add foreign key(crm_med) references medico(crm_med);
alter table paciente add cnpj_cli int;
alter table paciente add foreign key(cnpj_cli) references clinica(cnpj_cli);
alter table quarto add cpf_pac int;
alter table quarto add foreign key(cpf_pac) references paciente(cpf_pac);
alter table medico add cod_esp int;
alter table medico add foreign key(cod_esp) references especialidade(cod_esp);
alter table tratamento add crm_med int first;
alter table tratamento add foreign key(crm_med) references medico(crm_med);
alter table tratamento add cpf_pac int after crm_med;
alter table tratamento add foreign key(cpf_pac) references paciente(cpf_pac);
alter table formacao add cod_esp int first;
alter table formacao add foreign key(cod_esp) references especialidade(cod_esp);
alter table formacao add crm_med int after cod_esp;
alter table formacao add foreign key(crm_med) references medico(crm_med);

/*Adicionando dados na tabela*/
insert into clinica values
(12345, 'Clínica Boa Morte'), (22334, 'Clínica Até Logo');
insert into especialidade values
(1, 'Cardiologia'), (2, 'Ortopedia'), (3, 'Dermatologia'), (4, 'Otorrino'), (5, 'Clínica Médica'),
(6, 'Neurologia'), (7, 'Psiquiatria'), (8, 'Geriatria'), (9, 'Oftalmologia');
insert into medico values
(1234, 'Dino da Silva Sauro', '1950/10/10', 1590, 1), (2233, 'Ayrton Senna da Silva Sauro', '1965/11/01', 12000, 1),
(4646, 'Steve Jobs', '1975/03/26', 3900, 2), (1817, 'Bill Gates', '1966/09/09', 3899, 3), 
(4590, 'Lima Duarte', '1973/12/23', 5475.99, 3), (9088, 'Saddam Hussein', '1980/10/17', 7500, 5),
(7865, 'Osama Bin Laden', '1949/11/23', 507.5, 6), (1113, 'George W. Bush', '1959/08/08', 9200, 7),
(4566, 'Tiririca Abestado', '1977/12/01', 19500, 3), (1263, 'Fred Mercury Prateado', '1930/10/21', 1877.91, 5),
(4870, 'Maguila', '1920/05/28', 6200, 5);
insert into formacao values
(5, 4870, '1950/01/01', 'Faculdade do Boxe'), (2, 4870, '1960/09/11', 'Faculdade do Boxe'),
(5, 1263, '1975/11/23', 'Faculdade da Música Medicinal'), (3, 4566, '2006/12/02', 'Faculdade Tom Cavalcante'),
(7, 4566, '2008/12/23', 'Faculdade dos Abestados'), (7, 1113, '2005/02/22', 'MIT'),
(5, 9088, '1990/08/03', 'Universidade do Iraque'), (6, 7865, '2001/09/11', 'Universidade do Afeganistão'),
(9, 7865, '2001/09/11', 'Universidade das Bombas'), (1, 1234, '1965/11/23', 'Universidade dos Dinossauros'),
(3, 1817, '1995/04/18', 'Universidade das Antas');
insert into paciente values
(9010, 'Documentado Registrado da Silva', '1990/10/19', NULL, 1234, 22334),
(9011, 'Assumida Prometida de Souza', '2000/01/20', '(37) 8888-1234', 7865, 22334),
(9012, 'Acompanhado da Garrucha do Socorro', '1978/05/09', '(31) 3322-9090', 4566, 22334),
(9013, 'Maria do Futuro Comprometido', '2001/11/30', '(37) 9909-9909', 4566, 22334),
(9014, 'Ana Mariana Tertuliana Santana', '1955/09/19', NULL, 1263, 22334),
(9015, 'Mário Pelúcia Torres', '1980/06/30', '(11) 2104-4500', 1817, 12345),
(9016, 'Venezuela Boliviana Paraíba da Silva', '1949/02/11', '(34) 3344-5566', 1113, 12345),
(9017, 'José Coton Coteneto Paranhos', '1978/02/16', '(11) 8907-1299', 4646, 12345),
(9018, 'Gentleman Benvindo Welcomer da Silva', '1999/02/10', NULL, 1234, 12345),
(9019, 'Medula Óssea Trindade', '2005/10/23', '(37) 9900-0099', 4566, 12345);
insert into quarto values
(1, 1, 9018), (2, 1, 9011), (3, 2, 9014), (4, 2, 9015), (5, 4, 9012);
insert into tratamento values
(2233, 9016, '2007/02/01', '2007/03/01', 1500), (2233, 9016, '2008/05/20', '2008/05/25', 723.56),
(4646, 9013, '1996/10/15', '1996/10/15', 150), (4646, 9014, '2005/11/01', NULL, 0),
(4646, 9014, '2009/08/04', '2009/08/20', 2390), (1817, 9012, '2010/04/11', NULL, 0),
(1817, 9011, '2009/03/24', NULL, 0), (2233, 9015, '1997/12/25', NULL, 0),
(1234, 9015, '2010/04/18', '2010/04/18', 999.99), (1234, 9015, '1999/12/31', '2001/01/01', 3600),
(9088, 9018, '1994/10/01', NULL, 0), (9088, 9018, '1996/06/06', NULL, 0), 
(7865, 9018, '2002/09/11', '2005/06/22', 12979);

/*remover a clinica boa morte*/
SET foreign_key_checks = 0;
delete from clinica where cnpj_cli = 12345;

/*Selecionar todos os médicos que possuem formação na Universidade de Iraque*/
select crm_med from formacao where nom_fac = 'Universidade do Iraque';
select crm_med, nom_med, dat_nas, val_sal, cod_esp from medico where crm_med = 9088;

/*selecionar todos os médicos com crm entre 1000 e 8000*/
select crm_med, nom_med, dat_nas, val_sal, cod_esp from medico where crm_med between 1000 and 8000;

/*selecionar médico com maior salario*/
select max(val_sal) from medico;
select crm_med, nom_med, dat_nas, val_sal, cod_esp from medico where val_sal ='19500.00' ;

/*selecionar médico com menor salário*/
select min(val_sal) from medico;
select crm_med, nom_med, dat_nas, val_sal, cod_esp from medico where val_sal = '507.50';

/*Selecionar apenas o nome da faculdade de forma distinta da tabela formação*/
select distinct nom_fac from formacao;

/*inserir mais um médico na lista*/
insert into medico values
(6669, 'Senhora bisturi', '1966/07/13', 15908, 6);

/*Selecionar o nome do paciente com seu respectivo médico.*/
select paciente.nom_pac, medico.nom_med from tratamento inner join paciente on tratamento.cpf_pac = paciente.cpf_pac
inner join medico on tratamento.crm_med = medico.crm_med;

/*Selecionar o nome do paciente, o número do quarto, a data de início e fim da internação.*/
select paciente.nom_pac, quarto.num_qua, tratamento.dat_ini,tratamento.date_fin from tratamento
inner join paciente on tratamento.cpf_pac = paciente.cpf_pac
inner join quarto on paciente.cpf_pac = quarto.cpf_pac;

/*mostrar tabelas*/
select *from clinica;
select *from paciente;
select *from especialidade;
select *from quarto;
select *from formacao;
select *from medico;
select *from tratamento;


















