using Personal_Library.DataAbstractionLayer;
using Personal_Library.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Personal_Library.Controllers
{
    public class SearchBookController : Controller
    {
        private DAL dal = new DAL();

        public ActionResult Index()
        {
            return View("ViewSearchBook");
        }

        public ActionResult SearchBook(string genre)
        {
            string username = HttpContext.Session["user"].ToString();
            List<Book> books = dal.SearchBook(genre, username);

            Session["LastGenre"] = genre;

            return View("ViewSearchBook", books);
        }
    }
}