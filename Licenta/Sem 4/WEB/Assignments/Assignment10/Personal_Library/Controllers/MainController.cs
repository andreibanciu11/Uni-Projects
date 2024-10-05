using Personal_Library.DataAbstractionLayer;
using Personal_Library.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Personal_Library.Controllers
{
    public class MainController : Controller
    {

        private DAL dal = new DAL();
        
        public ActionResult Index()
        {
            string username = HttpContext.Session["user"].ToString();
            List<Book> books = dal.GetBooksForUser(username);

            return View("ViewMain", books);
        }

        public ActionResult GetBooks()
        {
            string username = HttpContext.Session["user"].ToString();
            List<Book> books = dal.GetBooksForUser(username);

            return View("ViewMain", books);
        }
    }
}