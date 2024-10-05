using Microsoft.SqlServer.Server;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace Personal_Library.Models
{
    public class User
    {
        private string username;
        private string password;

        public User(string v1, string v2)
        {
            this.username = v1;
            this.password = v2;
        }

        public string Username { get => username; set => username = value; }

        public string Password { get => password; set => password = value; }
    }
}