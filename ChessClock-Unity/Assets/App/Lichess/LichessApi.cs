using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using UnityEngine.Networking;

#if AHHFUCKIT_LOOK_AT_GATHER_CODE

namespace App.Lichess
{
    class LichessApi
    {
        public string GetMyInfo()
        {
            return MakeCall(MakeRequest("https://lichess.org/api/account"));
        }

        private UnityWebRequest MakeRequest(string endpointURL)
        {
            UnityWebRequest request = new UnityWebRequest(endpointURL);
            request.method = "GET";
            request.Headers.Add("Bearer", "gWOXNg6Itzc8KI04");
            return request;
        }

        private string MakeCall(HttpWebRequest request)
        {
            string responseText;
            try
            {
                using (var reader = new StreamReader(request.GetResponse().GetResponseStream()))
                {
                    responseText = reader.ReadToEnd();
                }
            }
            catch (Exception ex)
            {
                responseText = ex.Message;
            }
            return responseText;
        }
    }
}

#endif
