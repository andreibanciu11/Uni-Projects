using Personal_Library.DataAbstractionLayer;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Personal_Library.Controllers
{
    public class RemoveBookController : Controller
    {
        private DAL dal = new DAL();

        public ActionResult Index()
        {
            return View("ViewRemoveBook");
        }

        [HttpPost]
        public ActionResult RemoveBook(string author, string title)
        {
            string username = HttpContext.Session["user"].ToString();
            dal.RemoveBook(author, title, username);

            return Redirect("/Main");
           
        }
    }
}