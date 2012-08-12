<?php
/**
 * http://stackoverflow.com/questions/712392/send-email-using-gmail-smtp-server-from-php-page
 */
require_once "Mail.php";

class EMailClient{
    private static $CRLF = "\n";

	private $host;
	private $port;
    private $username;
    private $password;

    public function __construct($host, $port, $username, $password){
    	$this->host = $host;
    	$this->port = $port;
        $this->username = $username;
        $this->password = $password;
    }

    /**
     * TODO: support text and html encoding while sending messages
     * Enter description here ...
     * @param unknown_type $recipients
     * @param unknown_type $subject
     * @param unknown_type $message
     */
    public function sendMessage($recipients, $subject, $message){
        $headers = array ('From' => $this->username,'Subject' => $subject,'To' => join(",",$recipients));
        $config  = array ('host' => $this->host,
            'port' => $this->port,
            'auth' => true,
            'username' => $this->username,
            'password' => $this->password);
        $smtp = Mail::factory('smtp',$config);
        $mail = $smtp->send($recipients, $headers, $message);
        if (PEAR::isError($mail)) {
            throw new Exception("Failed to send mail: ".$mail);
        }
    }
}

/**
 $username = "<exchange_email_id>";
 $password = "<exchange_password>";
 $host = "<exchange_host>";
 $port = "587";
 $recipients = array();
 $recipients[] = "foo@gmail.com";
 $recipients[] = "bar@yahoo.com";
 $subject = "EMailClient PHP Test";
 $message = "Test successfull";
 $gmailClient = new EMailClient($host, $port, $username, $password);
 $gmailClient->sendMessage($recipients, $subject, $message);
 */
 

/**
 $username = "foo@gmail.com";
 $password = "<gmail_password>";
 $host = "ssl://smtp.gmail.com";
 $port = "465";
 $recipients = array();
 $recipients[] = "foo@gmail.com";
 $recipients[] = "bar@yahoo.com";
 $subject = "EMailClient PHP Test";
 $message = "Test successfull";
 $gmailClient = new EMailClient($host, $port, $username, $password);
 $gmailClient->sendMessage($recipients, $subject, $message);
 */ 
?>
