<?php

/**
 * Using MySQLi.
 * Only one connection is allowed.
 */
class Database {
	private $_connection;
	private static $_instance;

	/**
	 * Get instance of the Database.
	 * If instance does not exist, create one.
	 * @return Database
	 */
	public static function getInstance() {
		if ( ! self::$_instance ) {
			self::$_instance = new self();
		}

		return self::$_instance;
	}

	public function __construct() {
		/**
		 * MySQLi order = [host, username, password, database]
		 */
		$this->connection = new mysqli( 'localhost', 'username', 'password', 'database' );
		// Error handling.
		if ( mysqli_connect_error() ) {
			trigger_error( 'Failed to connect to Mysql: ' . mysqli_connect_error(), E_USER_ERROR );
		}
	}

	/**
	 * Magic method.
	 * is empty, because we want to prevent duplication.
	 */
	private function __clone() {
	}

	/**
	 * Return connection.
	 * @return mixed
	 */
	public function getConnection() {
		return $this->_connection;
	}

	protected function _example_select($city_name) {
		$db     = Database::getInstance();
		$mysqli = $db->getConnection();

		$query = 'SELECT column';
		$query .= 'FROM table ';

		$city = $mysqli->real_escape_string( $city_name );
		$query .= 'WHERE column = "' . $city . '";';

		$result = $mysqli->query($query);
		// If we found match.
		if ($row = $result->fetch_assoc()) {
		    return $row;
		} else {
			return FALSE;
		}
	}
}