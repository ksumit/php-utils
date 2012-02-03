<?php
/**
 * http://stackoverflow.com/questions/712392/send-email-using-gmail-smtp-server-from-php-page
 */
require_once "Mail.php";

class GMailClient{
    private static $HOST = "ssl://smtp.gmail.com";
    private static $PORT = "465";
    private static $CRLF = "\n";

    private $username;
    private $password;

    public function __construct($username, $password){
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
        $config  = array ('host' => self::$HOST,
            'port' => self::$PORT,
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
 $username = "";
 $password = "";
 $recipients = array();
 $recipients[] = "";
 $subject = "GMailClient PHP Test";
 $message = "Test successfull";
 $gmailClient = new GMailClient($username, $password);
 $gmailClient->sendMessage($recipients, $subject, $message);
 */
?>
