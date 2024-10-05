using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Personal_Library.Controllers
{
    public class LogoutController : Controller
    {
        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Logout()
        {
            // Clear the session and redirect to the login page
            HttpContext.Session.Clear();
            return Redirect("/Login");
        }
    }
}