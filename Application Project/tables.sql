create table admin
(
	username varchar(100),
	password varchar(100),
	primary key (username)
);


create table institute
(
	inst_name varchar(100),
	address varchar(100),
	primary key (name)
);


create table sports_officer
(
	so_id varchar(20),
	name varchar(20),
	phone varchar(20),
	inst_name varchar(100),
	primary key (so_id),
	foreign key (inst_name) references institute
		on delete cascade
);


create type sport_type as enum ('individual', 'team');
create table sport
(
	sport_name varchar(20),
	type sport_type,
	primary key (sport)	
);


-- create type participant_type as enum ('member', 'captain')
create table participant
(
	roll_id varchar(20),
	inst_name varchar(100),
	name varchar(20),
	phone varchar(20),
	sport_name varchar(20),
	primary key (roll_id, inst_name),
	foreign key (inst_name) references institute
		on delete cascade,
	foreign key (sport_name) references sport
		on delete cascade
)


create table referee
(
	referee_id varchar(20),
	referee_name varchar(20),
	sport_name varchar(20),
	phone varchar(20),
	primary key (referee_id),
	foreign key (sport_name) references sport
		on delete cascade
)


create table venue
(
	venue_id varchar(20),
	venue_name varchar(20),
	address varchar(100),
	primary key (venue_id)
)


create table group
(
	group_name varchar(20),
	sport_name varchar(20),
	winner varchar(100),
	primary key (group_name, sport_name),
	foreign key (sport_name) references sport
)


create table team_match
(
	match_id varchar(20),
	group_name varchar(20),
	venue_id varchar(20),
	date varchar(20),
	start_time varchar(20),
	referee_id varchar(20),
	winner 
)

create table plays_group
(
	group_name
)
