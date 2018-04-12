-- phpMyAdmin SQL Dump
-- version 4.1.14
-- http://www.phpmyadmin.net
--
-- Client :  127.0.0.1
-- Généré le :  Dim 30 Avril 2017 à 17:33
-- Version du serveur :  5.6.17
-- Version de PHP :  5.5.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Base de données :  `skylake2`
--

-- --------------------------------------------------------

--
-- Structure de la table `accounts`
--

CREATE TABLE IF NOT EXISTS `accounts` (
  `id` int(64) NOT NULL AUTO_INCREMENT,
  `username` varchar(32) NOT NULL,
  `password` varchar(64) NOT NULL,
  `email` varchar(64) NOT NULL,
  `lastOnlineUTC` int(64) NOT NULL,
  `coins` int(11) NOT NULL,
  `isGm` tinyint(1) NOT NULL,
  `remainingPlayTime` int(64) NOT NULL,
  `hardwareInfo` mediumblob,
  `accountSettings` longblob,
  `isOnline` tinyint(1) NOT NULL,
  `connectionIndex` int(64) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id_2` (`id`),
  UNIQUE KEY `username` (`username`),
  KEY `id` (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=15 ;

-- --------------------------------------------------------

--
-- Structure de la table `achievements`
--

CREATE TABLE IF NOT EXISTS `achievements` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `playerId` int(11) NOT NULL,
  `completed` blob,
  `inProgress` blob,
  `title` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Structure de la table `items`
--

CREATE TABLE IF NOT EXISTS `items` (
  `object_id` int(11) NOT NULL AUTO_INCREMENT,
  `player_id` int(11) NOT NULL,
  `item_id` int(11) NOT NULL,
  `uuid` varchar(128) NOT NULL,
  `data` mediumblob NOT NULL,
  PRIMARY KEY (`object_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=19 ;

-- --------------------------------------------------------

--
-- Structure de la table `npc_data`
--

CREATE TABLE IF NOT EXISTS `npc_data` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `version` varchar(128) NOT NULL,
  `data` blob,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Structure de la table `players`
--

CREATE TABLE IF NOT EXISTS `players` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `username` varchar(32) NOT NULL,
  `name` varchar(32) NOT NULL,
  `x` double NOT NULL,
  `y` double NOT NULL,
  `z` double NOT NULL,
  `h` int(16) NOT NULL,
  `race` int(11) NOT NULL,
  `gender` int(11) NOT NULL,
  `class` int(11) NOT NULL,
  `exp` int(11) NOT NULL,
  `restedExp` int(64) NOT NULL,
  `continent` int(64) NOT NULL,
  `level` int(11) NOT NULL,
  `details1` mediumblob,
  `details2` mediumblob,
  `details3` tinyblob,
  `lastOnlineUTC` int(64) NOT NULL,
  `creationTimeUTC` int(64) NOT NULL,
  `banTimeUTC` int(64) NOT NULL,
  `visitedSections` mediumblob,
  `worldMapGuardId` int(11) NOT NULL,
  `worldMapWorldId` int(11) NOT NULL,
  `worldMapSectionId` int(11) NOT NULL,
  `area` int(11) NOT NULL,
  `description` varchar(256) NOT NULL,
  `channel` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`),
  UNIQUE KEY `id` (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=5 ;

-- --------------------------------------------------------

--
-- Structure de la table `player_bank`
--

CREATE TABLE IF NOT EXISTS `player_bank` (
  `playerId` int(32) NOT NULL,
  `items` blob,
  `slotCount` int(11) NOT NULL,
  `gold` bigint(20) NOT NULL,
  PRIMARY KEY (`playerId`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Structure de la table `player_inventory`
--

CREATE TABLE IF NOT EXISTS `player_inventory` (
  `playerId` int(32) NOT NULL,
  `items` blob,
  `nonDbItems` mediumblob,
  `slotCount` int(11) NOT NULL,
  `gold` bigint(64) NOT NULL,
  PRIMARY KEY (`playerId`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Structure de la table `player_settings`
--

CREATE TABLE IF NOT EXISTS `player_settings` (
  `playerId` int(32) NOT NULL,
  `settings` longblob,
  PRIMARY KEY (`playerId`),
  UNIQUE KEY `name` (`playerId`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Structure de la table `player_skills`
--

CREATE TABLE IF NOT EXISTS `player_skills` (
  `playerId` int(32) NOT NULL,
  `active` mediumblob,
  `passive` mediumblob,
  `mounts` mediumblob,
  PRIMARY KEY (`playerId`),
  UNIQUE KEY `name` (`playerId`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
