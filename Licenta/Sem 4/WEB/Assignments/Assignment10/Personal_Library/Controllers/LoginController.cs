using Personal_Library.DataAbstractionLayer;
using Personal_Library.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Personal_Library.Controllers
{
    public class LoginController : Controller
    {
        private DAL dal = new DAL();

        public ActionResult Index()
        {
            return View("ViewLogin");
        }

        public ActionResult Login(string username, string password)
        {
            List<User> users = dal.GetAllUsers()
                .Where(user => user.Username.Equals(username) && user.Password.Equals(password)).ToList();
            if (users.Count.Equals(0))
            {
                return View("ViewLogin");
            }
            HttpContext.Session["user"] = username;
            return Redirect("/Main");
        }
    }
}