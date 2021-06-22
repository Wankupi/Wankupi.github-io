let isLocal = (location.hostname == "localhost" || location.hostname == "127.0.0.1");
let isMainPage = (location.pathname == "/");

var MathJax = { startup: { typeset: (!isMainPage), output: 'chtml' }, tex: { inlineMath: [['$', '$'], ['\\(', '\\)']] }, options: { enableMenu: false } };

function loadJs(src, config, func) {
  let d = document.createElement("script");
  d.src = src;
  for (i in config) d.setAttribute(i, config[i]);
  d.addEventListener("load", (e) => { (typeof (func) == "function") && func(e); e.target.remove(); });
  document.head.appendChild(d);
}

function loadCss(url) {
  let lnk = document.createElement("link");
  lnk.rel = "stylesheet";
  lnk.type = "text/css";
  lnk.href = url;
  document.head.appendChild(lnk);
}

loadJs(isLocal ? "/static/js/MathJax/es5/tex-chtml.js" : "https://cdn.jsdelivr.net/npm/mathjax/es5/tex-chtml.js", { id: "MathJax-script", async: "" });

if (!isLocal) {
  accessData = { url: location.pathname, hostname: location.hostname, ua: navigator.appVersion };
  if (localStorage["AV/0fXMSbCD7SIxO3z7u5j1VjkL-gzGzoHsz/currentUser"]) {
    let s = JSON.parse(localStorage["AV/0fXMSbCD7SIxO3z7u5j1VjkL-gzGzoHsz/currentUser"]);
    if (s.username) accessData.User = s.username;
  }
  fetch("https://0fxmsbcd.lc-cn-n1-shared.com/1.1/classes/AccessRecords", {
    headers: {
      "content-type": "application/json",
      "x-lc-id": "0fXMSbCD7SIxO3z7u5j1VjkL-gzGzoHsz",
      "x-lc-Key": "eIi8ECHYotfQqPB4AQRI6nfi"
    },
    body: JSON.stringify(accessData),
    method: "POST",
    mode: "cors"
  });
}

if (isMainPage) {
  loadJs(isLocal ? "/static/js/jquery/jquery.min.js" : "https://cdn.jsdelivr.net/npm/jquery@3.5.1/dist/jquery.min.js", { id: "jquery-script" }, () => {
    $(".scroll-down").on("click", function () { $("html,body").animate({ scrollTop: $("main").offset().top }, 1000); });
    $(".back-top").on("click", e => { $("html,body").animate({ scrollTop: 0 }, 1000); });
  });
}
else {
  document.title += " | Wankupi";

  loadCss("/static/css/highlight.css");

  loadJs("/static/js/highlight/highlight.pack.js", { async: true }, () => { hljs.initHighlighting(); });

  loadJs("https://cdn.jsdelivr.net/npm/valine/dist/Valine.min.js", { async: "" }, () => {
    new Valine({
      el: '#Comment',
      app_id: '0fXMSbCD7SIxO3z7u5j1VjkL-gzGzoHsz',
      app_key: 'eIi8ECHYotfQqPB4AQRI6nfi',
      placeholder: '写下你的精彩评论！',
      lang: 'zh-CN',
      visitor: true,
      recordIP: true,
      enableQQ: true,
      requiredFields: ['nick', 'mail']
    });
  });
}