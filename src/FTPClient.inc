<?php
class FTPClient{
    private static $TIME_OUT = 60;
    private $ftpserver;
    private $ftpport;
    private $ftpuser;
    private $ftppasswd;
    private $conn_id = FALSE;

    /**
     * TODO: support other constructors
     * Enter description here ...
     * @param unknown_type $ftpserver
     * @param unknown_type $ftpport
     * @param unknown_type $ftpuser
     * @param unknown_type $ftppasswd
     */
    public function __construct($ftpserver,$ftpport,$ftpuser, $ftppasswd){
        $this->ftpserver = $ftpserver;
        $this->ftpport = $ftpport;
        $this->ftpuser = $ftpuser;
        $this->ftppasswd =$ftppasswd;
    }

    public function connect($passive=FALSE) {
        $this->conn_id = ftp_connect($this->ftpserver, $this->ftpport, self::$TIME_OUT);
        if (!$this->conn_id ){
            throw new Exception("Failed to connect to ".$this->ftpserver.":".$this->ftpport);
        }
        if(!ftp_login($this->conn_id, $this->ftpuser, $this->ftppasswd)){
            $this->disconnect();
            throw new Exception("Failed to login");
        }
        ftp_pasv($this->conn_id, $passive);
    }

    public function isConnected(){
        return ($this->conn_id != FALSE);
    }

    private function checkConnected(){
        if(!$this->isConnected()){
            throw new Exception("Not connected");
        }
    }

    public function upload($localpath, $remotepath){
        $this->checkConnected();

        $remotedir = dirname($remotepath);
        if(!$this->exists($remotedir)){
            ftp_mkdir($this->conn_id,$remotedir);
        }
        $upload = ftp_put($this->conn_id, $remotepath, $localpath, FTP_BINARY);
        if(!$upload){
            throw new Exception("Failed to upload");
        }
    }

    public function exists($remotepath){
        $this->checkConnected();
        $list = ftp_nlist($this->conn_id, $remotepath);
        return ($list && (sizeof($list)>0));// >1 for the case it's a directory
    }

    public function disconnect(){
        if($this->isConnected()){
            ftp_close($this->conn_id);
            $this->conn_id = FALSE;
        }
    }

    /**
     * TODO: support for ftpuser and/or ftppasswd being empty
     * Enter description here ...
     */
    public function __toString(){
        $string = array("ftp://");
        $string[] = $this->ftpuser;
        $string[] =":";$string[] =$this->ftppasswd;
        $string[] ="@";
        $string[] =$this->ftpserver;
        $string[] =":";
        $string[] =$this->ftpport;
        return join("", $string);
    }
}
/**
 require_once "FTPClient.inc";

 $ftpserver = "localhost";
 $ftpport = "21";
 $ftpuser   = "";
 $ftppasswd   = "";
 $localpath = "/tmp/foo.txt";
 $remotepath   = "/tmp/newfoo.txt";

 $ftpClient = new FTPClient($ftpserver, $ftpport, $ftpuser, $ftppasswd);
 $ftpClient->connect();
 $ftpClient->upload($localpath, $remotepath);
 $exists = $ftpClient->exists($remotepath);
 $ftpClient->disconnect();
 echo $exists;
 */
?>
